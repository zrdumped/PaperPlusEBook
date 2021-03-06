//========================================================================
//
// pdfsig.cc
//
// This file is licensed under the GPLv2 or later
//
// Copyright 2015 André Guerreiro <aguerreiro1985@gmail.com>
// Copyright 2015 André Esser <bepandre@hotmail.com>
// Copyright 2015, 2017, 2018 Albert Astals Cid <aacid@kde.org>
// Copyright 2016 Markus Kilås <digital@markuspage.com>
// Copyright 2017 Hans-Ulrich Jüttner <huj@froreich-bioscientia.de>
// Copyright 2017 Adrian Johnson <ajohnson@redneon.com>
// Copyright 2018 Chinmoy Ranjan Pradhan <chinmoyrp65@protonmail.com>
//
//========================================================================

#include "config.h"
#include <poppler-config.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <hasht.h>
#include <fstream>
#include "parseargs.h"
#include "Object.h"
#include "Array.h"
#include "Page.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "Error.h"
#include "GlobalParams.h"
#include "SignatureInfo.h"
#include "Win32Console.h"
#include "numberofcharacters.h"

static const char * getReadableSigState(SignatureValidationStatus sig_vs)
{
  switch(sig_vs) {
    case SIGNATURE_VALID:
      return "Signature is Valid.";

    case SIGNATURE_INVALID:
      return "Signature is Invalid.";

    case SIGNATURE_DIGEST_MISMATCH:
      return "Digest Mismatch.";

    case SIGNATURE_DECODING_ERROR:
      return "Document isn't signed or corrupted data.";

    case SIGNATURE_NOT_VERIFIED:
      return "Signature has not yet been verified.";

    default:
      return "Unknown Validation Failure.";
  }
}

static const char * getReadableCertState(CertificateValidationStatus cert_vs)
{
  switch(cert_vs) {
    case CERTIFICATE_TRUSTED:
      return "Certificate is Trusted.";

    case CERTIFICATE_UNTRUSTED_ISSUER:
      return "Certificate issuer isn't Trusted.";

    case CERTIFICATE_UNKNOWN_ISSUER:
      return "Certificate issuer is unknown.";

    case CERTIFICATE_REVOKED:
      return "Certificate has been Revoked.";

    case CERTIFICATE_EXPIRED:
      return "Certificate has Expired";

    case CERTIFICATE_NOT_VERIFIED:
      return "Certificate has not yet been verified.";

    default:
      return "Unknown issue with Certificate or corrupted data.";
  }
}

static char *getReadableTime(time_t unix_time)
{
  char * time_str = (char *) gmalloc(64);
  strftime(time_str, 64, "%b %d %Y %H:%M:%S", localtime(&unix_time));
  return time_str;
}

static void dumpSignature(int sig_num, int sigCount, FormWidgetSignature *sig_widget, const char *filename)
{
    const GooString *signature = sig_widget->getSignature();
    if (!signature) {
        printf("Cannot dump signature #%d\n", sig_num);
        return;
    }

    const int sigCountLength = numberOfCharacters(sigCount);
    // We want format to be {0:s}.sig{1:Xd} where X is sigCountLength
    // since { is the magic character to replace things we need to put it twice where
    // we don't want it to be replaced
    GooString *format = GooString::format("{{0:s}}.sig{{1:{0:d}d}}", sigCountLength);
    GooString *path = GooString::format(format->getCString(), basename(filename), sig_num);
    printf("Signature #%d (%u bytes) => %s\n", sig_num, signature->getLength(), path->getCString());
    std::ofstream outfile(path->getCString(), std::ofstream::binary);
    outfile.write(signature->getCString(), signature->getLength());
    outfile.close();
    delete format;
    delete path;
}

static GBool printVersion = gFalse;
static GBool printHelp = gFalse;
static GBool dontVerifyCert = gFalse;
static GBool dumpSignatures = gFalse;

static const ArgDesc argDesc[] = {
  {"-nocert", argFlag,     &dontVerifyCert,     0,
   "don't perform certificate validation"},
  {"-dump",   argFlag,     &dumpSignatures,     0,
   "dump all signatures into current directory"},

  {"-v",      argFlag,     &printVersion,  0,
   "print copyright and version info"},
  {"-h",      argFlag,     &printHelp,     0,
   "print usage information"},
  {"-help",   argFlag,     &printHelp,     0,
   "print usage information"},
  {"-?",      argFlag,     &printHelp,     0,
   "print usage information"},
  {}
};


int main(int argc, char *argv[])
{
  PDFDoc *doc = nullptr;
  unsigned int sigCount;
  GooString * fileName = nullptr;
  SignatureInfo *sig_info = nullptr;
  char *time_str = nullptr;
  std::vector<FormWidgetSignature*> sig_widgets;
  globalParams = new GlobalParams();

  Win32Console win32Console(&argc, &argv);
  int exitCode = 99;
  GBool ok;

  ok = parseArgs(argDesc, &argc, argv);

  if (!ok || argc != 2 || printVersion || printHelp) {
    fprintf(stderr, "pdfsig version %s\n", PACKAGE_VERSION);
    fprintf(stderr, "%s\n", popplerCopyright);
    fprintf(stderr, "%s\n", xpdfCopyright);
    if (!printVersion) {
      printUsage("pdfsig", "<PDF-file>", argDesc);
    }
    if (printVersion || printHelp)
      exitCode = 0;
    goto end;
  }

  fileName = new GooString(argv[argc - 1]);

  // open PDF file
  doc = PDFDocFactory().createPDFDoc(*fileName, nullptr, nullptr);

  if (!doc->isOk()) {
    exitCode = 1;
    goto end;
  }

  sig_widgets = doc->getSignatureWidgets();
  sigCount = sig_widgets.size();

  if (sigCount >= 1) {
    if (dumpSignatures) {
      printf("Dumping Signatures: %u\n", sigCount);
      for (unsigned int i = 0; i < sigCount; i++) {
        dumpSignature(i, sigCount, sig_widgets.at(i), fileName->getCString());
      }
      goto end;
    } else {
      printf("Digital Signature Info of: %s\n", fileName->getCString());
    }
  } else {
    printf("File '%s' does not contain any signatures\n", fileName->getCString());
    exitCode = 2;
    goto end;
  }

  for (unsigned int i = 0; i < sigCount; i++) {
    sig_info = sig_widgets.at(i)->validateSignature(!dontVerifyCert, false, -1 /* now */);
    printf("Signature #%u:\n", i+1);
    printf("  - Signer Certificate Common Name: %s\n", sig_info->getSignerName());
    printf("  - Signer full Distinguished Name: %s\n", sig_info->getSubjectDN());
    printf("  - Signing Time: %s\n", time_str = getReadableTime(sig_info->getSigningTime()));
    printf("  - Signing Hash Algorithm: ");
    switch (sig_info->getHashAlgorithm())
    {
      case HASH_AlgMD2:
        printf("MD2\n");
        break;
      case HASH_AlgMD5:
        printf("MD5\n");
        break;
      case HASH_AlgSHA1:
        printf("SHA1\n");
        break;
      case HASH_AlgSHA256:
        printf("SHA-256\n");
        break;
      case HASH_AlgSHA384:
        printf("SHA-384\n");
        break;
      case HASH_AlgSHA512:
        printf("SHA-512\n");
        break;
      case HASH_AlgSHA224:
        printf("SHA-224\n");
        break;
      default:
        printf("unknown\n");
    }
    printf("  - Signature Type: ");
    switch (sig_widgets.at(i)->signatureType())
    {
      case adbe_pkcs7_sha1:
        printf("adbe.pkcs7.sha1\n");
        break;
      case adbe_pkcs7_detached:
        printf("adbe.pkcs7.detached\n");
        break;
      case ETSI_CAdES_detached:
        printf("ETSI.CAdES.detached\n");
        break;
      default:
        printf("unknown\n");
    }
    std::vector<Goffset> ranges = sig_widgets.at(i)->getSignedRangeBounds();
    if (ranges.size() == 4)
    {
      printf("  - Signed Ranges: [%lld - %lld], [%lld - %lld]\n",
             ranges[0], ranges[1], ranges[2], ranges[3]);
      Goffset checked_file_size;
      GooString* signature = sig_widgets.at(i)->getCheckedSignature(&checked_file_size);
      if (signature && checked_file_size == ranges[3])
      {
        printf("  - Total document signed\n");
        delete signature;
      }
      else
        printf("  - Not total document signed\n");
    }
    printf("  - Signature Validation: %s\n", getReadableSigState(sig_info->getSignatureValStatus()));
    gfree(time_str);
    if (sig_info->getSignatureValStatus() != SIGNATURE_VALID || dontVerifyCert) {
      continue;
    }
    printf("  - Certificate Validation: %s\n", getReadableCertState(sig_info->getCertificateValStatus()));
  }

  exitCode = 0;

end:
  delete globalParams;
  delete fileName;
  delete doc;

  return exitCode;
}
