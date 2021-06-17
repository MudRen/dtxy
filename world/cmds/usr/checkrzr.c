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
		return notify_fail("�����̫����, С�Ļ��ȥ");
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
                        msg += "�� " + NOR;
			msg += rzr->query("family/family_name") + " " + rzr->query("name") + "("
			       + rzr->query("id") + ") ����(" + env->query("short");
			if (wizardp(this_player()))
			    	msg+= " - " + file_name(env);
		    msg += ")";
		    if (wizardp(this_player())) {
				msg += " ��ѧ(" + rzr->query("combat_exp") + ") ����(" + rzr->query("daoxing") + ") ��("
				       + rzr->query("kee") + ") ��(" + rzr->query("sen") +")";
			} else {
				msg += " ��ѧ(" + RANK_D->describe_exp(rzr->query("combat_exp")) + ") ����("
					+ RANK_D->describe_dx(rzr->query("daoxing")) + ")";
			}

			if ( rzr->is_fighting() )
				msg+= "    "HIR"<ս����>"NOR ;
			msg += "\n";

			msg += "==========================================================\n";
			real_count++;
		}
		msg += "ϵͳ�й��� " + real_count + " ��������\n";
		me->add("sen", -300);
		tell_object( me, msg);
		me->start_busy(3);
		return 1;
	} else {
		return notify_fail("ָ���ʽ��checkrzr all|rzr_id|rzr_name\n");
	}

}

int help(object me)
{
write(@HELP
ָ���ʽ : checkrzr all|rzr_id|rzr_name

���ָ������г�������ϵͳ�е������ˡ�

-all �г����е������ˡ�
-rzr_id �г��ض��������˵���ϸ��Ϣ���������˵�ID������
-rzr_name �г��ض��������˵���ϸ��Ϣ���������˵�����������
HELP
	);
	return 1;
}


