PORTNAME=	amnezia-go
PORTVERSION=	0.2.16
CATEGORIES=	net net-vpn
MASTER_SITES=	https://github.com/amnezia-vpn/amneziawg-go/

MAINTAINER=	vova@zote.me
COMMENT=	Amnezia implementation in Go with Amnezia VPN non-detection extensions
WWW=		https://github.com/amnezia-vpn/amneziawg-go/

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		gmake go:modules

GO_MODULE=	github.com/amnezia-vpn/amneziawg-go@v${PORTVERSION}

PLIST_FILES=	bin/${PORTNAME}

.include <bsd.port.mk>
