#ifndef __MUDLIB__
#define __MUDLIB__

//  The base distribution mudlib name.

#define MUDLIB_NAME                             "YWX人造人 大唐西游"
#define MUDLIB_VERSION_NUMBER	"1.0"
#define MUDLIB_VERSION			(MUDLIB_NAME + " " + MUDLIB_VERSION_NUMBER)

#define INTERMUD_MUD_NAME               "YWXRZRDTXY"
#define INTERMUD_NAME                   "YWX人造人 大唐西游"
#define CHINESE_MUD_NAME                "YWX人造人 大唐西游"
#define MUD_ADMIN                       "ywxemotion@yahoo.com"
#define MUD_WEB                           "http://ywxrzrdtxy.jumbocool.com/"
#define MUDLIB_ENCODING                    "GB"

// mon 4/27/98 for "vote" command and the piggy room.
#define MAX_VOTES_PER_SITE   2
// maximum votes accepted for one site.
#define VOTER_SITE   0
// this defines what is one voting site. can either be 0 or 1.
// 0: use the first 3 fields of numerical IP as a site.
// 1: use the full 4 fileds of numerical IP as a site.

#define GB_AND_BIG5
// define this to allow both GB and BIG5 players.
// undefine will only allow GB players.

#undef INTERMUD_ALL_MUD
// define this if want to connect with ALL muds.
// undef this if only want to connect with Chinese Muds.
// Chinese muds is defined as either their mudlib is ES2 or they
// have ENCODING field set.


#endif
