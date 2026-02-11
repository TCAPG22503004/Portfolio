@echo off

rem ---------------------------
rem List of File 
rem (Link from under to upper)
rem ---------------------------
set f0=main
set f1=title
set f2=config
set f3=game
set f4=player
set f5=object
set f6=perspective
set f7=quaternion
set f8=write




rem ------------------------------
rem Not need to change under here
rem ------------------------------

rem -- create variable of file's name --

setlocal enabledelayedexpansion
set fc= 
set fo= 
set i=0

:FOREACH_FILELIST
set f=!f%i%!
if defined f (
	set fc=%f%.cpp %fc%
	set fo=%f%.o %fo%
	set /a i+=1
	goto :FOREACH_FILELIST
)



rem -- Build and execute --

cd ../src
g++ -c %fc% -I../../../../../DxLibFile -I../include -DDX_GCC_COMPILE
g++ %fo% -o ../build/fly.exe -L../../../../../DxLibFile -lDxLib -lDxUseCLib -lDxDrawFunc -ljpeg -lpng -lzlib -ltiff -ltheora_static -lvorbis_static -lvorbisfile_static -logg_static -lbulletdynamics -lbulletcollision -lbulletmath -lopusfile -lopus -lsilk_common -lcelt -Wl,-subsystem,windows
del *.o
cd ../build/
start fly.exe
cd ../src
