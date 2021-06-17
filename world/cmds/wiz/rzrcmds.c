#include <ansi.h>
#include <net/dns.h>
#define MANMADE_NPC "/jjhome/npc/manmade_npc"
#define JJ_MANMADE_NPCD "/jjhome/daemon/jj_manmade_npcd"
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mixed main(object me, string arg)
{
	if (!arg)
		return notify_fail("ָ���ʽ��rzrcmds smashall\n");
	if ( arg == "smashall" ) {
		JJ_MANMADE_NPCD->destroy_all_npcs();
	} else if (arg == "shuffle") {
		JJ_MANMADE_NPCD->shuffle_npc();
	} else if (arg == "enable_debug_skip_npc") {
		JJ_MANMADE_NPCD->set_debug_skip_npc(1);
	} else if (arg == "disable_debug_skip_npc") {
		JJ_MANMADE_NPCD->set_debug_skip_npc(0);
	}
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : checkrzr smashall

������ϵͳָ�

-smashall �ݻ����е������ˡ�
-shuffle ���·���������
-enable_debug_skip_npc
-disable_debug_skip_npc
HELP
	);
	return 1;
}


