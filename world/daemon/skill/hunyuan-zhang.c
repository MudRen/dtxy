//lestat 2001 for dtxy
//Ϊ�����������޸�
// hunyuan-zhang.c ��Ԫ��
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$Nһʽ"+HIW"�����Ƴ�ᶡ�"+NOR"��˫�Ƽ�����һ�ŵ����İ�����������$n��$l",
        "dodge":     15,
        "parry":     -5,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$N��ָ�罣��һʽ"+RED"���׺���ա�"+NOR"������$n��$l��ȥ",
        "dodge":     15,
        "parry":     -5,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ"+WHT"���ƶ����롹"+NOR"������΢��������է��է�ϣ��͵ز���$n��$l",
        "dodge":     15,
        "parry":     -5,
        "force" : 190,
        "damage_type" : "����"
]),
([      "action" : "$N˫����������������һʽ"+HIG"�����ɴ�䡹"+NOR"���ó�������̵����룬������$n��ȥ",
        "dodge":     15,
        "parry":     -5,
        "force" : 200,
        "damage_type" : "����"
]),
([      "action" : "$N��������һ�ݣ�ʹ��һʽ"+HIB"����������"+NOR"��˫�Ʋ�£����ֱ����$n��$l��ȥ",
        "dodge":     15,
        "parry":     -5,
        "force" : 160,
        "damage_type" : "����"
]),
([      "action" : "$N����һ�䣬ʹһʽ"+YEL"���ޱ���ľ��"+NOR"��˫�ƴ�����ɲ�ľ������͵ػ���$n��$l",
        "dodge":     15,
        "parry":     -5,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ"+HIC"����ɽ��ˮ��"+NOR"���������أ�������ӯ��ͬʱ��$n��$l��ȥ",
        "dodge":     15,
        "parry":     -5,
        "force" : 120,
        "damage_type" : "����"
]),
([      "action" : "$Nͻ��һ��"+HIY"���������á�"+NOR"��˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
        "dodge":     15,
        "parry":     -5,
        "force" : 100,
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ"+WHT"��������ơ�"+NOR"��˫�������һ����裬�����ѻ���$n��$l��",
        "dodge":     15,
        "parry":     -5,
        "force" : 210,
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ"+HIG"������Ʈ�졹"+NOR"����������������˫��һ��һ�ͣ����Ƽ򵥣�ȴ��$n�޷�����",
        "dodge":     15,
        "parry":     -5,
        "force" : 180,
        "damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="unarmed" ; }

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("����Ԫ�Ʊ�����֡�\n");
        if ((int)me->query_skill("zixia-shengong", 1) < 20)
                return notify_fail("�����ϼ�񹦻�򲻹����޷�ѧ��Ԫ�ơ�\n");
        if ((int)me->query("max_force") < 100)
                return notify_fail("�������̫�����޷�����Ԫ�ơ�\n");
        return 1;
}

int practice_skill(object me)
{
        if ((int)me->query("kee") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("force") < 40)
                return notify_fail("���������������Ԫ�ơ�\n");
        me->receive_damage("kee", 30);
        me->add("force", -10);
        return 1;
}

string perform_action_file(string action)
{
        return CLASS_D("shushan") +"/hunyuan-zhang/" + action;
}