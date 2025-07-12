PORTNAME=	wireguard-amnezia
PORTVERSION=	1.0.4
DISTVERSIONPREFIX=	v
CATEGORIES=	net net-vpn
PKGNAMESUFFIX=	-kmod

MAINTAINER=	vova@zote.me
COMMENT=	WireGuard implementation with Amnezia support
WWW=		https://github.com/vgrebenschikov/wireguard-amnezia-kmod

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		kmod uidfix
USE_GITHUB=	yes
GH_ACCOUNT=	vgrebenschikov
GH_PROJECT=	wireguard-amnezia-kmod

PLIST_FILES=	${KMODDIR}/if_wg.ko

.include <bsd.port.mk>
