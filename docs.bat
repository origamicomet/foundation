@echo off
doxygen docs/conf.doxygen
pushd docs
sphinx-build -b html . _build
popd ..
