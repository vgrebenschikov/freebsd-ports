PORTNAME=	GraphicsMagick
PORTVERSION=	1.3.43
PORTREVISION=	3
PORTEPOCH=	1
CATEGORIES=	graphics
MASTER_SITES=	SF

MAINTAINER=	sunpoet@FreeBSD.org
COMMENT=	Fast image processing tools based on ImageMagick
WWW=		https://graphicsmagick.sourceforge.io/ \
		http://www.graphicsmagick.org/

LICENSE=	MIT

USES=		cpe libtool localbase:ldflags pathfix pkgconfig tar:xz

CONFIGURE_ARGS=	--enable-shared --enable-static \
		--with-windows-font-dir=${WINDOWS_FONT_DIR} \
		--without-dps --without-gdi32 --without-perl --without-trio
CONFIGURE_ENV=	PTHREAD_LIBS=-lpthread
GNU_CONFIGURE=	yes
INSTALL_TARGET=	install-strip
TEST_TARGET=	check
USE_LDCONFIG=	yes

FLAVORS=	x11 nox11
FLAVOR?=	${FLAVORS:[1]}
nox11_PKGNAMESUFFIX=	-nox11
.if ${FLAVOR} == x11
CONFIGURE_ARGS+=--with-x
USE_XORG=	ice sm x11 xext
USES+=		xorg
.else
CONFIGURE_ARGS+=--without-x ac_cv_lib_ICE_IceConnectionNumber=no
.endif

PORTSCOUT=	limit:^[0-9]\.[0-9]\.[1-9][0-9\]$$

# Use fonts installed by x11-fonts/webfonts by default
WINDOWS_FONT_DIR?=	${LOCALBASE}/share/fonts/webfonts

OPTIONS_DEFINE=	BZIP2 DOCS FPX FREETYPE HEIF JASPER JBIG JPEG JXL LCMS2 LZMA OPENMP Q8BIT PNG TEST TIFF WEBP WMF XML ZLIB ZSTD
OPTIONS_DEFAULT=BZIP2 FREETYPE JASPER JBIG JPEG JXL LCMS2 LZMA OPENMP PNG TIFF WEBP WMF XML ZLIB
Q8BIT_DESC=	Use 8-bit pixels (speed) instead of 16-bit (quality)
TEST_DESC=	Run bundled self-tests after build

BZIP2_CONFIGURE_WITH=	bzlib
FPX_CONFIGURE_WITH=	fpx
FPX_LDFLAGS=		-lfpx
FPX_LIB_DEPENDS=	libfpx.so:graphics/libfpx
FREETYPE_CONFIGURE_WITH=ttf
FREETYPE_LIB_DEPENDS=	libfreetype.so:print/freetype2
HEIF_CONFIGURE_WITH=	heif
HEIF_LIB_DEPENDS=	libheif.so:graphics/libheif
JASPER_CONFIGURE_WITH=	jp2
JASPER_LIB_DEPENDS=	libjasper.so:graphics/jasper
JBIG_CONFIGURE_WITH=	jbig
JBIG_LIB_DEPENDS=	libjbig.so:graphics/jbigkit
JPEG_CONFIGURE_WITH=	jpeg
JPEG_USES=		jpeg
JXL_CONFIGURE_WITH=	jxl
JXL_LIB_DEPENDS=	libjxl.so:graphics/libjxl
LCMS2_CONFIGURE_WITH=	lcms2
LCMS2_LIB_DEPENDS=	liblcms2.so:graphics/lcms2
LZMA_CONFIGURE_WITH=	lzma
OPENMP_CONFIGURE_OFF=	--disable-openmp --without-threads
OPENMP_CONFIGURE_ON=	--disable-openmp-slow --enable-openmp --with-threads
PNG_CONFIGURE_WITH=	png
PNG_LIB_DEPENDS=	libpng.so:graphics/png
Q8BIT_CONFIGURE_OFF=	--with-quantum-depth=16
Q8BIT_CONFIGURE_ON=	--with-quantum-depth=8
Q8BIT_PLIST_SUB=	Q=8
Q8BIT_PLIST_SUB_OFF=	Q=16
TEST_BUILD_DEPENDS=	webfonts>=0:x11-fonts/webfonts
TEST_RUN_DEPENDS=	webfonts>=0:x11-fonts/webfonts
TIFF_CONFIGURE_WITH=	tiff
TIFF_LIB_DEPENDS=	libtiff.so:graphics/tiff
WEBP_CONFIGURE_WITH=	webp
WEBP_LIB_DEPENDS=	libwebp.so:graphics/webp
WMF_CONFIGURE_WITH=	wmf
WMF_LIB_DEPENDS=	libwmf.so:graphics/libwmf@${FLAVOR}
XML_CONFIGURE_WITH=	xml
XML_USE=		GNOME=libxml2
XML_USES=		gnome
ZLIB_CONFIGURE_WITH=	zlib
ZSTD_CONFIGURE_WITH=	zstd
ZSTD_LIB_DEPENDS=	libzstd.so:archivers/zstd

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MOPENMP}
.if ${ARCH} != aarch64 && ${ARCH} != amd64 && ${ARCH} != i386 && ${ARCH} != powerpc64 && ${ARCH} != powerpc64le && ${ARCH} != riscv64
USES+=		compiler:gcc-c++11-lib
.endif
.endif

post-install-Q8BIT-off:
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/GraphicsMagick/modules-Q16/coders ${STAGEDIR}${PREFIX}/lib/GraphicsMagick/modules-Q16/filters

post-install-Q8BIT-on:
	${MKDIR} ${STAGEDIR}${PREFIX}/lib/GraphicsMagick/modules-Q8/coders ${STAGEDIR}${PREFIX}/lib/GraphicsMagick/modules-Q8/filters

.include <bsd.port.mk>
