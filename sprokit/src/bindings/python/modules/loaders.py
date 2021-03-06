# Copyright (C) 2011 by Calvin Spealman (ironfroggy@gmail.com)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
#     The above copyright notice and this permission notice shall be included in
#     all copies or substantial portions of the Software.
#
#     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#     THE SOFTWARE.

# Other authors:
# Calvin Spealman ironfroggy@gmail.com @ironfroggy http://github.com/ironfroggy
# Dustin Lacewell dlacewell@gmail.com @dustinlacewell http://github.com/dustinlacewell
# Erik Youngren artanis.00@gmail.com http://artanis00.blogspot.com/ http://github.com/Artanis

# From: https://github.com/ironfroggy/straight.plugin
# Commit: be4c0113629557e02602f9720adb07634eb9d274

# Only ModuleLoader is here since we only care about it.

"""Facility to load plugins."""

import sys
import os

from importlib import import_module


class Loader(object):

    def __init__(self, *args, **kwargs):
        self._cache = []

    def load(self, *args, **kwargs):
        self._fill_cache(*args, **kwargs)
        self._post_fill()
        self._order()
        return self._cache

    def _meta(self, plugin):
        meta = getattr(plugin, '__plugin__', None)
        return meta

    def _post_fill(self):
        for plugin in self._cache:
            meta = self._meta(plugin)
            if not getattr(meta, 'load', True):
                self._cache.remove(plugin)
            for implied_namespace in getattr(meta, 'imply_plugins', []):
                plugins = self._cache
                self._cache = self.load(implied_namespace)
                self._post_fill()
                self._cache = plugins + self._cache

    def _order(self):
        self._cache.sort(key=self._plugin_priority, reverse=True)

    def _plugin_priority(self, plugin):
        meta = self._meta(plugin)
        return getattr(meta, 'priority', 0.0)


class ModuleLoader(Loader):
    """Performs the work of locating and loading straight plugins.

    This looks for plugins in every location in the import path.
    """

    def _isPackage(self, path):
        pkg_init = os.path.join(path, '__init__.py')
        if os.path.exists(pkg_init):
            return True

        return False

    def _findPluginFilePaths(self, namespace):
        already_seen = set()

        # Look in each location in the path
        for path in sys.path:

            # Within this, we want to look for a package for the namespace
            namespace_rel_path = namespace.replace(".", os.path.sep)
            namespace_path = os.path.join(path, namespace_rel_path)
            if os.path.exists(namespace_path):
                for possible in os.listdir(namespace_path):

                    poss_path = os.path.join(namespace_path, possible)
                    if os.path.isdir(poss_path):
                        if not self._isPackage(poss_path):
                            continue
                        base = possible
                    else:
                        base, ext = os.path.splitext(possible)
                        if base == '__init__' or ext != '.py':
                            continue

                    if base not in already_seen:
                        already_seen.add(base)
                        yield os.path.join(namespace, possible)

    def _findPluginModules(self, namespace):
        for filepath in self._findPluginFilePaths(namespace):
            path_segments = list(filepath.split(os.path.sep))
            path_segments = [p for p in path_segments if p]
            path_segments[-1] = os.path.splitext(path_segments[-1])[0]
            import_path = '.'.join(path_segments)

            try:
                module = import_module(import_path)
            except ImportError:
                #raise Exception(import_path)

                module = None

            if module is not None:
                yield module

    def _fill_cache(self, namespace):
        """Load all modules found in a namespace"""

        modules = self._findPluginModules(namespace)

        self._cache = list(modules)
