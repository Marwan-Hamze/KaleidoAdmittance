#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define KaleidoAdmittance_DLLIMPORT __declspec(dllimport)
#  define KaleidoAdmittance_DLLEXPORT __declspec(dllexport)
#  define KaleidoAdmittance_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define KaleidoAdmittance_DLLIMPORT __attribute__((visibility("default")))
#    define KaleidoAdmittance_DLLEXPORT __attribute__((visibility("default")))
#    define KaleidoAdmittance_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define KaleidoAdmittance_DLLIMPORT
#    define KaleidoAdmittance_DLLEXPORT
#    define KaleidoAdmittance_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef KaleidoAdmittance_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define KaleidoAdmittance_DLLAPI
#  define KaleidoAdmittance_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef KaleidoAdmittance_EXPORTS
#    define KaleidoAdmittance_DLLAPI KaleidoAdmittance_DLLEXPORT
#  else
#    define KaleidoAdmittance_DLLAPI KaleidoAdmittance_DLLIMPORT
#  endif // KaleidoAdmittance_EXPORTS
#  define KaleidoAdmittance_LOCAL KaleidoAdmittance_DLLLOCAL
#endif // KaleidoAdmittance_STATIC