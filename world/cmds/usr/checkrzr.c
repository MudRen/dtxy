#include <ansi.h>
#include <net/dns.h>
#define MANMADE_NPC "/jjhome/npc/manmade_npc"
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

mixed main(object me, string arg)
{
	int count, i, real_count;
	string msg;
	object *rzrs;
	object rzr;
	object env;
	int sen;
	if ( me->is_busy() )
		return notify_fail("You are busy!\n");
	sen = me->query("sen", 1);
	if ( sen < 350 )
		return notify_fail("你的神太低了, 小心昏过去");
	if ( arg == "all" ) {
		rzrs = children(MANMADE_NPC);
		count = sizeof(rzrs);
		msg = "==========================================================\n";
		for (i = 0; i < count; i++) {
			int level;
			rzr = rzrs[i];
			env = environment(rzr);
			if (!env) continue;
			level = rzr->rzr_get_my_level();
			switch(level) {
				case 0:
					msg += HIB;
					break;
				case 1:
					msg += HIY;
					break;
				case 2:
					msg += HIM;
					break;
				case 3:
					msg += HIC;
					break;
				case 4:
				default:
					msg += HIW;
					break;

			}
			msg = msg + level;
                        msg += "级 " + NOR;
			msg += rzr->query("family/family_name") + " " + rzr->query("name") + "("
			       + rzr->query("id") + ") 正在(" + env->query("short");
			if (wizardp(this_player()))
			    	msg+= " - " + file_name(env);
		    msg += ")";
		    if (wizardp(this_player())) {
				msg += " 武学(" + rzr->query("combat_exp") + ") 道行(" + rzr->query("daoxing") + ") 气("
				       + rzr->query("kee") + ") 神(" + rzr->query("sen") +")";
			} else {
				msg += " 武学(" + RANK_D->describe_exp(rzr->query("combat_exp")) + ") 道行("
					+ RANK_D->describe_dx(rzr->query("daoxing")) + ")";
			}

			if ( rzr->is_fighting() )
				msg+= "    "HIR"<战斗中>"NOR ;
			msg += "\n";

			msg += "==========================================================\n";
			real_count++;
		}
		msg += "系统中共有 " + real_count + " 个人造人\n";
		me->add("sen", -300);
		tell_object( me, msg);
		me->start_busy(3);
		return 1;
	} else {
		return notify_fail("指令格式：checkrzr all|rzr_id|rzr_name\n");
	}

}

int help(object me)
{
write(@HELP
指令格式 : checkrzr all|rzr_id|rzr_name

这个指令可以列出所有在系统中的人造人。

-all 列出所有的人造人。
-rzr_id 列出特定的人造人的详细信息。用人造人的ID来查找
-rzr_name 列出特定的人造人的详细信息。用人造人的名字来查找
HELP
	);
	return 1;
}


