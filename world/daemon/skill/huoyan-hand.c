// huoyan-hand.c ���浶
// /daemon/skill/huoyan-hand.c
// writted by mind 2001/2

inherit SKILL;
#include <ansi.h>
mapping *action = ({
([      "action" : "$Nʹ��һ��"+HIR"����ľȡ��"NOR+"������ת��˫����ǰƽƽ����$n",
        "skill_name" : "��ľȡ��",
        "force" : 100,
        "dodge":                -10,
        "parry":                -10,
        "damage_type" : "����",
        "weapon" :              "˫��",
]),
([      "action" : "$Nʹ��һ��"+HIR"��ף�ڻ��桹"NOR+"�������絶��бб����$n��$l",
        "skill_name" : "ף�ڻ���",
        "force" : 120,
        "dodge":                -10,
        "parry":                -20,
        "damage_type" : "����",
        "weapon":               "������",
]),
([      "action" : "$Nʹ��һ��"+HIR"��ҵ���ޱߡ�"NOR+"��˫��һ�ģ�һ�����������й���$n��$l",
        "skill_name" : "ҵ���ޱ�",
        "force" : 140,
        "dodge":                0,
        "parry":                -30,
        "damage_type" : "����",
        "weapon" :              "˫��",
]),
([      "action" : "$Nʹ��һ��"+HIR"�������ֻء�"NOR+"��˫�ֺ�ʮ����ͷ����$n",
        "skill_name" : "�����ֻ�",
        "force" : 160,
        "dodge":        -30,
        "parry":        10,
        "damage_type" : "����",
        "weapon" :              "˫��",
]),
([      "action" : "$Nʹ��һ��"+HIR"��˫�����桹"NOR+"��˫��һ�������������湥��$n��$l",
        "skill_name" : "˫������",
        "force" : 180,
        "dodge":                10,
        "parry":                -30,
        "damage_type" : "����",
        "weapon":               "����",
]),
([      "action" : "$Nʹ��һ��"+HIR"����ɽ�𺣡�"NOR+"��˫������б�ģ���ʱ��ǧ������������˷�����$n",
        "skill_name" : "��ɽ��",
        "force" : 200,
        "dodge":                -40,
        "parry":                -40,
        "damage_type" : "����",
        "weapon" :              "˫��",
]),
([      "action" : "$Nʹ��һ��"+HIR"���������ˡ�"NOR+"����ۻ��գ�����������ֱ��$n��$l",
        "skill_name" : "��������",
        "force" : 220,
        "dodge":                0,
        "parry":                20,
        "damage_type" : "����",
        "weapon":               "������",
]),
([      "action" : "$Nʹ��һ��"+HIR"������������"NOR+"��˫��΢��������ǰ�죬һ���ھ�����ɽ�����㹥��$n",
        "skill_name" : "��������",
        "force" : 250,
        "dodge":                20,
        "parry":                -50,
        "damage_type" : "����",
        "weapon":               "����",
]),
});


int valid_enable(string usage)
{
        return usage=="unarmed";
}


int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����浶������֡�\n");

        if ((int)me->query("max_force") < 200)  
                return notify_fail("�������������\n");

                return 1;
}



mapping query_action(object me, object weapon)
{
   if (random(me->query_skill("unarmed",1)) > 60 &&
   me->query_skill("force",1) > 60 &&
   me->query("force") > 100 ) {
   me->add("force", -100);
   return ([
   "action": "$N����ȫ��֮����һ��"+HIR"�������Ի�"NOR+"�������ޱȵػ���$n",
   "force": 400,
   "damage_type": "����",]);
    }
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����浶������֡�\n");
        if ((int)me->query("sen") < 40)
                return notify_fail("������������������˻��浶��\n");
        if( (int)me->query("force") < 40 )
                return notify_fail("������������ˡ�\n");

        me->receive_damage("sen", 30);
        me->add("force", -20);
        write(RED"˫�Ƴ�죬ϸϸ������ָ���۶��ϡ�\n"NOR);
        return 1;
}

void skill_improved(object me)
{
        if( (int)me->query_skill("huoyan-hand", 1)  % 10 == 0 ) {
                tell_object(me,
                        RED "\n��ͻȻ����һ�ɶ���������ͷ��ֻ������ɱ��....\n\n" NOR);
                me->add("bellicosity", 50);
        }
        if( !me->query("m_success/��������") && (int)me->query_skill("bingpo-hand", 1)>80 && (int)me->query_skill("huoyan-hand", 1)>80){
        me->set_skill("ice_fire_zhang",40);
        me->delete_skill("bingpo-hand");
        me->delete_skill("huoyan-hand");        
                tell_object(me,"���ڻ��˱��ǵ��ͻ��浶�ľ��⣬������Բ���������ã������"+chinese_number(40)+"�����������ơ�\n");
                me->set("m_success/��������",1);
                
                }
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/huoyan-hand/" + func;
}
