project = 'pow-blockchain'
copyright = '2025, gdaneek'
author = 'gdaneek'
release = '1.0.0'

extensions = ['breathe', 'exhale', 'sphinx_rtd_theme']
breathe_projects = {
    "My C++ Project": "../../build/xml"
}
breathe_default_project = "My C++ Project"

templates_path = ['_templates']
exclude_patterns = []

exhale_args = {
    "containmentFolder": "api",
    "rootFileName": "library_root.rst",
    "rootFileTitle": "API Reference",
    "doxygenStripFromPath": "..",
    "createTreeView": True,
    "exhaleExecutesDoxygen": False,
}

html_theme = 'sphinx_rtd_theme'
