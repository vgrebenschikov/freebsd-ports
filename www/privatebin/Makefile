PORTNAME=	privatebin
PORTVERSION=	2.0.0
CATEGORIES=	www security

MAINTAINER=	dvl@FreeBSD.org
COMMENT=	Simple end-to-end encrypting zero-knowledge paste-bin server
WWW=		https://privatebin.info/

LICENSE=	ZLIB
LICENSE_FILE=	${WRKSRC}/LICENSE.md

USES=		cpe php

SUB_FILES=	pkg-message
SUB_LIST=	PORTNAME=${PORTNAME}

NO_BUILD=	yes
NO_ARCH=	yes

USE_PHP=	ctype filter gd zlib
USE_GITHUB=	yes
GH_PROJECT=	PrivateBin

OPTIONS_DEFINE=	DOCS

post-patch:
	@${REINPLACE_CMD} -e 's:%%DATADBDIR%%:/var/db/${PORTNAME}:' \
		${WRKSRC}/index.php

do-install:
	@${MKDIR} ${STAGEDIR}${WWWDIR}
	@cd ${WRKSRC} && ${COPYTREE_SHARE} . ${STAGEDIR}${WWWDIR}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${MV} ${STAGEDIR}/${WWWDIR}/*.md ${STAGEDIR}/${DOCSDIR}
	@${MKDIR} ${STAGEDIR}/var/db/${PORTNAME}

.include <bsd.port.mk>
