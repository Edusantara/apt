// -*- mode: cpp; mode: fold -*-
// Description								/*{{{*/
/* ######################################################################

   Here be cows – but: Never ask, never tell

   ##################################################################### */
									/*}}}*/
// Include Files							/*{{{*/
#include<config.h>

#include <apt-pkg/configuration.h>
#include <apt-pkg/cmndline.h>
#include <apt-pkg/strutl.h>

#include <strings.h>
#include <sstream>

#include "private-moo.h"
#include "private-output.h"

#include <apti18n.h>
									/*}}}*/

std::string getMooLine() {						/*{{{*/
   time_t const timenow = time(NULL);
   struct tm special;
   localtime_r(&timenow, &special);
   enum { NORMAL, PACKAGEMANAGER, APPRECIATION, AGITATION, AIRBORN } line;
   if (special.tm_mon == 11 && special.tm_mday == 25)
      line = PACKAGEMANAGER;
   else if (special.tm_mon == 7 && special.tm_mday == 16)
      line = APPRECIATION;
   else if (special.tm_mon == 10 && special.tm_mday == 7)
      line = AGITATION;
   else if (special.tm_mon == 1 && special.tm_mday == 18)
      line = AIRBORN;
   else
      line = NORMAL;

   bool const quiet = _config->FindI("quiet") >= 2;
   std::ostringstream out;
   if (quiet == false)
      out << "...\"";

   switch(line)
   {
      case PACKAGEMANAGER: out << "Happy package management day!"; break;
      case APPRECIATION:   out << "Three moos for Debian!"; break;
      case AGITATION:      out << "Whoever needs milk, bows to the animal."; break;
      case AIRBORN:        out << "It's a Bird ... It's a Plane ... It's Super Cow!"; break;
      default:             out << "Have you mooed today?"; break;
   }

   if (quiet == true)
      out << std::endl;
   else
      out << "\"..." << std::endl;

   return out.str();
}
									/*}}}*/
bool printMooLine() {							/*{{{*/
   std::cerr << getMooLine() << std::endl;
   return true;
}
									/*}}}*/
bool DoMoo1(CommandLine &CmdL)						/*{{{*/
{
   // our trustworthy super cow since 2001
   if (_config->FindI("quiet") >= 2)
      return printMooLine();
   std::string const moo = getMooLine();
   size_t const depth = moo.length()/4;
   c1out <<
      OutputInDepth(depth, " ") << "         (__) \n" <<
      OutputInDepth(depth, " ") << "         (oo) \n" <<
      OutputInDepth(depth, " ") << "   /------\\/ \n" <<
      OutputInDepth(depth, " ") << "  / |    ||   \n" <<
      OutputInDepth(depth, " ") << " *  /\\---/\\ \n" <<
      OutputInDepth(depth, " ") << "    ~~   ~~   \n" <<
      moo;
   return true;
}
									/*}}}*/
bool DoMoo2(CommandLine &CmdL)						/*{{{*/
{
   // by Fernando Ribeiro in lp:56125
   if (_config->FindI("quiet") >= 2)
      return printMooLine();
   std::string const moo = getMooLine();
   size_t const depth = moo.length()/4;
   if (_config->FindB("APT::Moo::Color", false) == false)
      c1out <<
	 OutputInDepth(depth, " ") << "         (__)  \n" <<
	 OutputInDepth(depth, " ") << " _______~(..)~ \n" <<
	 OutputInDepth(depth, " ") << "   ,----\\(oo) \n" <<
	 OutputInDepth(depth, " ") << "  /|____|,'    \n" <<
	 OutputInDepth(depth, " ") << " * /\"\\ /\\   \n" <<
	 OutputInDepth(depth, " ") << "   ~ ~ ~ ~     \n" <<
	 moo;
   else
   {
      c1out <<
	 OutputInDepth(depth, " ") << "         \e[1;97m(\e[0;33m__\e[1;97m)\e[0m\n" <<
	 OutputInDepth(depth, " ") << " \e[31m_______\e[33m~(\e[1;34m..\e[0;33m)~\e[0m\n" <<
	 OutputInDepth(depth, " ") << "   \e[33m,----\e[31m\\\e[33m(\e[1;4;35moo\e[0;33m)\e[0m\n" <<
	 OutputInDepth(depth, " ") << "  \e[33m/|____|,'\e[0m\n" <<
	 OutputInDepth(depth, " ") << " \e[1;5;97m*\e[0;33m /\\  /\\\e[0m\n" <<
	 "\e[32m";
      for (size_t i = moo.length()/2; i > 1; --i)
	 c1out << "wW";

      c1out << "w\e[0m\n" << moo;
   }

   return true;
}
									/*}}}*/
bool DoMoo3(CommandLine &CmdL)						/*{{{*/
{
   // by Robert Millan in deb:134156
   if (_config->FindI("quiet") >= 2)
      return printMooLine();
   std::string const moo = getMooLine();
   size_t const depth = moo.length()/16;
   c1out <<
      OutputInDepth(depth, " ") << "                   \\_/ \n" <<
      OutputInDepth(depth, " ") << " m00h  (__)       -(_)- \n" <<
      OutputInDepth(depth, " ") << "    \\  ~Oo~___     / \\\n" <<
      OutputInDepth(depth, " ") << "       (..)  |\\        \n" <<
      OutputInDepth(depth, "_") << "_________|_|_|__________" <<
      OutputInDepth((moo.length() - (depth + 27)), "_") << "\n" << moo;
   return true;
}
									/*}}}*/
bool DoMooApril(CommandLine &CmdL)					/*{{{*/
{
   // by Christopher Allan Webber and proposed by Paul Tagliamonte
   // in a "Community outreach": https://lists.debian.org/debian-devel/2013/04/msg00045.html
   if (_config->FindI("quiet") >= 2)
   {
      std::cerr << "Have you smashed some milk today?" << std::endl;
      return true;
   }
   c1out <<
      "               _     _\n"
      "              (_\\___( \\,\n"
      "                )___   _  Have you smashed some milk today?\n"
      "               /( (_)-(_)    /\n"
      "    ,---------'         \\_\n"
      "  //(  ',__,'      \\  (' ')\n"
      " //  )              '----'\n"
      " '' ; \\     .--.  ,/\n"
      "    | )',_,'----( ;\n"
      "    ||| '''     '||\n";
   return true;
}
									/*}}}*/
bool DoMoo(CommandLine &CmdL)						/*{{{*/
{
   time_t const timenow = time(NULL);
   struct tm april;
   localtime_r(&timenow, &april);
   if (april.tm_mday == 1 && april.tm_mon == 3)
      return DoMooApril(CmdL);

   signed short SuperCow = 1;
   if (CmdL.FileSize() != 0)
      for (const char **Moo = CmdL.FileList + 1; *Moo != 0; Moo++)
         if (strcasecmp(*Moo, "moo") == 0)
            SuperCow++;

   // time is random enough for our purpose
   if (SuperCow > 3)
   {
      if (april.tm_sec == 1)
	 SuperCow = 1 + (timenow % 4);
      else
	 SuperCow = 1 + (timenow % 3);
   }

   switch(SuperCow) {
      case 1: return DoMoo1(CmdL);
      case 2: return DoMoo2(CmdL);
      case 3: return DoMoo3(CmdL);
      case 4: return DoMooApril(CmdL);
      default: return DoMoo1(CmdL);
   }

   return true;
}
									/*}}}*/
