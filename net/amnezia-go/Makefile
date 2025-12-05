PORTNAME=	amnezia-go
PORTVERSION=	0.2.16
PORTREVISION=	1
CATEGORIES=	net net-vpn
MASTER_SITES=	https://github.com/amnezia-vpn/amneziawg-go


MAINTAINER=	vova@zote.me
COMMENT=	WireGuard implementation in Go with Amnezia VPN non-detection extensions
WWW=		https://www.wireguard.com

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake go:modules,no_targets tar:xz

USE_GITHUB=	yes
GH_ACCOUNT=	amnezia-vpn
GH_PROJECT=	amneziawg-go
GH_TAGNAME=	v0.2.16

PLIST_FILES=	bin/${GH_PROJECT}

.include <bsd.port.mk>
