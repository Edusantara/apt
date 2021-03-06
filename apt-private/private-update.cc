// Include files							/*{{{*/
#include<config.h>

#include <apt-pkg/aptconfiguration.h>
#include <apt-pkg/error.h>
#include <apt-pkg/cmndline.h>
#include <apt-pkg/init.h>
#include <apt-pkg/depcache.h>
#include <apt-pkg/sourcelist.h>
#include <apt-pkg/algorithms.h>
#include <apt-pkg/acquire-item.h>
#include <apt-pkg/strutl.h>
#include <apt-pkg/fileutl.h>
#include <apt-pkg/clean.h>
#include <apt-pkg/srcrecords.h>
#include <apt-pkg/version.h>
#include <apt-pkg/cachefile.h>
#include <apt-pkg/cacheset.h>
#include <apt-pkg/sptr.h>
#include <apt-pkg/md5.h>
#include <apt-pkg/versionmatch.h>
#include <apt-pkg/progress.h>
#include <apt-pkg/pkgsystem.h>
#include <apt-pkg/pkgrecords.h>
#include <apt-pkg/indexfile.h>
#include <apt-pkg/update.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "private-cachefile.h"
#include "private-output.h"
#include "acqprogress.h"

#include <apti18n.h>
									/*}}}*/

// DoUpdate - Update the package lists					/*{{{*/
// ---------------------------------------------------------------------
/* */
bool DoUpdate(CommandLine &CmdL)
{
   if (CmdL.FileSize() != 1)
      return _error->Error(_("The update command takes no arguments"));

   CacheFile Cache;

   // Get the source list
   if (Cache.BuildSourceList() == false)
      return false;
   pkgSourceList *List = Cache.GetSourceList();

   // Create the progress
   AcqTextStatus Stat(ScreenWidth,_config->FindI("quiet",0));
      
   // Just print out the uris an exit if the --print-uris flag was used
   if (_config->FindB("APT::Get::Print-URIs") == true)
   {
      // force a hashsum for compatibility reasons
      _config->CndSet("Acquire::ForceHash", "md5sum");

      // get a fetcher
      pkgAcquire Fetcher;
      if (Fetcher.Setup(&Stat) == false)
	 return false;

      // Populate it with the source selection and get all Indexes 
      // (GetAll=true)
      if (List->GetIndexes(&Fetcher,true) == false)
	 return false;

      pkgAcquire::UriIterator I = Fetcher.UriBegin();
      for (; I != Fetcher.UriEnd(); ++I)
	 c1out << '\'' << I->URI << "' " << flNotDir(I->Owner->DestFile) << ' ' << 
            I->Owner->FileSize << ' ' << I->Owner->HashSum() << std::endl;
      return true;
   }

   // do the work
   if (_config->FindB("APT::Get::Download",true) == true)
       ListUpdate(Stat, *List);

   // Rebuild the cache.
   if (_config->FindB("pkgCacheFile::Generate", true) == true)
   {
      pkgCacheFile::RemoveCaches();
      if (Cache.BuildCaches() == false)
	 return false;
   }

   return true;
}
									/*}}}*/
