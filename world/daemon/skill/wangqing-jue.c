// Wangqing-jue.c �����
// Cracked by �辪ѩ 4-17-2003

#include <ansi.h>
inherit SKILL;

mapping *action = ({
	([	"name":		"�����",
                "action":       "$Nʹ��������е�"+HIC"���������"NOR+"$N�ѷ·������ں���һ����ɲ�Ǽ���ǲԲ���񷣬���޵�ֹ��Ҳû�и��顣",
		"dodge":	-30,
		"parry" :	-30,
		"force":	20,
        	"damage" :      70,
		"damage_type":	"����"
	]),
	([	"name":		"�����",
                "action":       "$Nʹ��������е�"+HIC"���������"NOR+"$N�ѷ·������ں���һ����ɲ�Ǽ���ǲԲ���񷣬���޵�ֹ��Ҳû�и��顣",
		"dodge":	-30,
		"parry" :	-30,
		"force":	20,
        	"damage" :      70,
		"damage_type":	"����"
	]),
	([	"name":		"���ƾ�",
             "action":       "$Nʹ��������е�"+YEL"�����ƾ���"NOR+"��$N��ʱ������ǣ��ٵ���϶���˻�����",
		"dodge":	-30,
		"parry" :	-30,
		"force":	30,
        	"damage" :      70,
		"damage_type":	"����"
	]),
	([	"name":		"������",
		"action":	"$N�ٽ���ü����ׯ������$w�������ڰ�գ�ңָ$n��ʹ�����齣���е�"+HIR"����������"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	40,
        	"damage" :      70,
		"damage_type":	"����"
	]),
	([	"name":		"��˼��",
		"action":	"$Nʹ��������е�"+HIB"����˼����"NOR+"����һЩ���������ơ����֡���������ס$n���Ծ���������������ʹ$n׹�������³���֮��",
		"dodge":	-30,
		"parry" :	-30,
		"force":	50,
        	"damage" :      70,
		"damage_type":	"����"
	]),
	([	"name":		"ʦ�̾�",
		"action":	"$Nʹ��������е�"+HIY"��ʦ�̾���"NOR+"��ٿ��һ������������ȥ��һ���֣���ժ�±����$w�������ࡱ������һ��������",
		"dodge":	-30,
		"parry" :	-30,
		"force":	60,
        	"damage" :      80,
		"damage_type":	"����"
	]),
	([	"name":		"������",
		"action":	"$Nֻ��һ�ɹ���ؾó��ĺ����������м���ȫ��ʹ��������е�"+HIW"����������"NOR+"����Ϯ$n",
		"dodge":	-30,
		"parry" :	-30,
		"force":	70,
        	"damage" :      90,
		"damage_type":	"����"
	]),
	([	"name":		"������",
		"action":	"$nֻ����һ��ǿ���ѹ��������ǵص�ӿѹ������������Ȼ�к�������������е�"+HIG"����������"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	80,
        	"damage" :      100,
		"damage_type":	"����"
	]),
	([	"name":		"�����",
		"action":	"$n��Ҫ�̳�����Ȼ���÷�ӿ�ƶ�������$Nһ���Զ����裬���˽�ȥ,   ����"+HIC"���������"NOR,
		"dodge":	-30,
		"parry" :	-30,
		"force":	90,
        	"damage" :      100,
		"damage_type":	"����"
	]),
});

int valid_learn(object me)
{
//        if (me->query("mark/jinlong")!="wangqing")
//                return notify_fail("������ʵ���޷��������������ôѧ����û���κγ�����\n"); 
	return 1;
}

int valid_enable(string usage)
{
        return  (usage=="parry") || (usage=="sword") || (usage=="dodge");
}

mapping query_action(object me, object weapon)
{
	int i;
	i = me->query_temp("WQJ");
	if( !me->query_temp("WQJ") ) {
        return action[random(9)];
	}
	else
	{
	return action[i];
	}
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30 
        ||    (int)me->query("force") < 5  )
                return
	notify_fail("����������������Ź��򣬻�������Ϣ��Ϣ�ɡ�\n");
//        if (me->query("mark/jinlong")!="wangqing")
//                return notify_fail("����ô������û���κγ�����\n"); 
        if( (int)me->query_skill("wangqing-jue",1) < 40 )
                return notify_fail("�������������򻹲�����û�а취������ϰ���׽�����\n");
        me->receive_damage("kee", 20);
        me->add("force", -5);
	return 1;
}

string *dodge_msg = ({
       "$nʩ��"+HIC"�����⡱"NOR+"����$n��������Ծ��ƽ���ӳ�������һ�㣬���Ʒ��������һ�ۣ������˳�ȥ��\n",
       "$nʩ��"+HIB"�����ơ�"NOR+"������δ�أ�����ȴ�ӵص��ɶ������������ǣ�б�����䡣\n",
       "$nһ�㣬�ּ��س������ȥ�ƾ�����$n�ڽ�����ӳҫ�������ȸ�������ƿն�ȥ������"+HIY"��������"NOR+"һ����\n",
	"$nʩչ�ˡ���������е�"+HIC"����ӳ��"+NOR"��������ɫ��������ʧ�ˡ�\n",   
       "����΢�磬��ɼ������������,$n������Ҷ����Ʈ��$N��������"+HIG"��������"NOR+"һ����\n",
});

string *parry_msg = ({
       "$n��"+HIY"����Ͼ���"NOR+"֮�ƣ�������$N֮��,����$N����һ�ִ��.\n",
      "$n����ɲ�Ǽ䣬��������һ����ľ������˲�佫���е�Ѩ��ȫ������.����"+HIG"��ľ�����"NOR"\n",
       "$n����"+HIC"��ˮ�ž���"NOR+"��$n��Χ������������ˮ����$N������ȫ����ˮǽ�ϣ����޷�͸��.\n",
	"$n����ңԶ�Ļ��ҡ�Σ���"+HIR"�����Ӿ���"NOR+"֮�ƣ�������Ŀ,����һ��.\n",
	"$n��"+YEL"�����ھ���"NOR+"Ѹ�ٵ��ڵ��Ͼ򿪶�,$n������\n",
});


string query_parry_msg(object weapon)
{
                return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

string perform_action_file(string func)
{
return CLASS_D("suburb") + "/wangqing-jue/" + func;
}

