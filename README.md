# AutoPatcher-vs2013
Auto-patcher upgrade to 2013

-- fixes --
*subdirectory bug fixed (like "lib/xml/parser") </br>
added secondary server (if it cannot reach the main server, it connects to the second)</br>

-- Libraries -- </br>

Boost 1.66.0 ( ```<1.34> upgrade, concerted```) </br>
Z-lib 1.2.3 (no upgrade, concerted) </br>
wxWidgets 2.8.10 ( ```upgrade and renewal ```) </br>
tinyXml 2.6.1 (no upgrade, concerted) </br>
libtorrent 1.1.12 ( ```<0.15.5> upgrade, renewal ```) </br>
minilzo 2.03 (no upgrade) </br>
cryptopp ( ```upgrade ```) </br>

-- canceled libs -- </br>
Mantle (re-created what is needed) </br>
YmirBase-locale-network </br>
Earth (re-created what is needed -- EA::Status -> CStatus) </br>
gtest </br>
7zip </br>
Reducio </br>


-- build -- </br>
*zlib-1.2.3\projects\visualc6\zlib.sln (vs2013 -- "LIB Release") </br>
*wxWidgets-2.8.10\build\msw\wx.sln (vs2013 -- "Release") </br>
*tinyxml (vs2013 -- "Release|Debug") </br>
