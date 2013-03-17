@echo off

:Parse
if "%1"=="" (
  goto End
)

if "%1"=="--config=debug" (
  echo CONFIG_FOUNDATION_DEBUG=y > tup.config
  goto End
)

if "%1"=="--config=release" (
  echo CONFIG_FOUNDATION_DEBUG=n > tup.config
  goto End
)

if "%1"=="--clean" (
  goto Clean
)

if "%1"=="--build" (
  goto Build
)

if "%1"=="--generate-tests" (
  goto GenerateTests
)

shift
goto Parse

:GenerateTests
goto End

:Build
call "%VCINSTALLDIR%\vcvarsall.bat"
echo Run `tup upd`
goto End

:Clean
for /r %%f in (*.o) do (
  if exist %%f del %%f )
for /r %%f in (*.pdb) do (
  if exist %%f del %%f )
for /r %%f in (*.lib) do (
  if exist %%f del %%f )
goto End

:End