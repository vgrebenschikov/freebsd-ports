PORTNAME=	sshguard
PORTVERSION=	2.5.77
PORTREVISION=	0
PORTEPOCH=	1
CATEGORIES=	security

USE_GITHUB=	yes
GH_ACCOUNT=	vgrebenschikov
GH_PROJECT=	sshguard
GH_TAGNAME=	v2.5.77

MAINTAINER=	kevinz5000@gmail.com
COMMENT=	Protect hosts from brute-force attacks against SSH and other services
WWW=		https://www.sshguard.net/

LICENSE=	BSD2CLAUSE

USES=		autoreconf python:build
USE_RC_SUBR=	sshguard

BUILD_DEPENDS=	rst2man:textproc/py-docutils

GNU_CONFIGURE=	yes

SUB_FILES=	pkg-message

post-patch:
	@${REINPLACE_CMD} -e 's|%PREFIX%|${PREFIX}|' \
		${WRKSRC}/doc/sshguard.8.rst
	@${REINPLACE_CMD} -e 's|/usr/local|${PREFIX}|' \
		${WRKSRC}/examples/sshguard.conf.sample

post-install:
	${MKDIR} ${STAGEDIR}${PREFIX}/etc
	${INSTALL_DATA} ${WRKSRC}/examples/sshguard.conf.sample \
		${STAGEDIR}${PREFIX}/etc

.include <bsd.port.mk>
