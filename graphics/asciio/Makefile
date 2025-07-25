PORTNAME=	asciio
PORTVERSION=	1.9.02
PORTREVISION=	2
PORTEPOCH=	1
CATEGORIES=	graphics
MASTER_SITES=	https://cpan.metacpan.org/authors/id/N/NK/NKH/ \
		LOCAL/ehaupt
DISTNAME=	App-Asciio-${PORTVERSION}

MAINTAINER=	ehaupt@FreeBSD.org
COMMENT=	Perl/GTK application that lets you draw ASCII charts using a GUI
WWW=		https://metacpan.org/release/App-Asciio

LICENSE=	ART10 GPLv1+
LICENSE_COMB=	dual

BUILD_DEPENDS=	p5-Algorithm-Diff>=0:devel/p5-Algorithm-Diff \
		p5-Check-ISA>=0:devel/p5-Check-ISA \
		p5-Compress-Bzip2>=0:archivers/p5-Compress-Bzip2 \
		p5-Data-Compare>=0:devel/p5-Data-Compare \
		p5-Data-TreeDumper-Renderer-GTK>=0:devel/p5-Data-TreeDumper-Renderer-GTK \
		p5-Directory-Scratch>=0:devel/p5-Directory-Scratch \
		p5-Eval-Context>=0:devel/p5-Eval-Context \
		p5-File-HomeDir>=0:devel/p5-File-HomeDir \
		p5-Gtk3>=0:x11-toolkits/p5-Gtk3 \
		p5-Hash-Slice>=0.03:devel/p5-Hash-Slice \
		p5-IO-Prompter>=0:devel/p5-IO-Prompter \
		p5-List-MoreUtils>=0:lang/p5-List-MoreUtils \
		p5-Module-Util>=0:devel/p5-Module-Util \
		p5-Pango>0:x11-toolkits/p5-Pango \
		p5-Sereal>=0:converters/p5-Sereal \
		p5-Sub-Exporter>=0:devel/p5-Sub-Exporter \
		p5-Term-ReadKey>0:devel/p5-Term-ReadKey \
		p5-Term-Size-Any>=0:devel/p5-Term-Size-Any \
		p5-Term-TermKey>=0:devel/p5-Term-TermKey \
		p5-Text-Diff>=1.41:textproc/p5-Text-Diff
RUN_DEPENDS:=	${BUILD_DEPENDS} \
		p5-Class-ISA>=0:devel/p5-Class-ISA
TEST_DEPENDS=	p5-Test-NoWarnings>=0:devel/p5-Test-NoWarnings \
		p5-Test-Warn>=0:devel/p5-Test-Warn

USES=		perl5
USE_PERL5=	modbuild
NO_ARCH=	yes

.include <bsd.port.mk>
