PORTNAME=	junos-eznc
DISTVERSION=	2.7.0
PORTREVISION=	3
CATEGORIES=	net-mgmt python
MASTER_SITES=	PYPI
PKGNAMEPREFIX=	${PYTHON_PKGNAMEPREFIX}

MAINTAINER=	sergey@akhmatov.ru
COMMENT=	Junos easy automation for non-programmers
WWW=		https://github.com/Juniper/py-junos-eznc

LICENSE=	APACHE20

RUN_DEPENDS=	${PYTHON_PKGNAMEPREFIX}Jinja2>=2.7.1:devel/py-Jinja2@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}lxml5>=3.2.4:devel/py-lxml5@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}ncclient>=0.6.15:net-mgmt/py-ncclient@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}paramiko>=1.15.2:security/py-paramiko@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyparsing>0:devel/py-pyparsing@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}scp>=0.7.0:security/py-scp@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyserial>0:comms/py-pyserial@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}six>0:devel/py-six@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}transitions>0:devel/py-transitions@${PY_FLAVOR} \
		${PYTHON_PKGNAMEPREFIX}pyyaml>=5.1:devel/py-pyyaml@${PY_FLAVOR}	\
		${PYTHON_PKGNAMEPREFIX}yamlordereddictloader>0:devel/py-yamlordereddictloader@${PY_FLAVOR}

USES=		python
USE_PYTHON=	distutils autoplist

NO_ARCH=	yes

.include <bsd.port.mk>
