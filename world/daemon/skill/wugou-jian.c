inherit SKILL;
#include <ansi.h>
mapping *action = ({
([      "name":   "��������徻̨",
    "action" : "$N������ת�����ֽ�ָ������ǰ��һ�紦�̴ٶ�������\n"
    "һ��"BLINK""HIR"����������徻̨��"NOR"������$w���������һ�����϶�������$n��",
    "dodge" : -5,
    "damage" : 15,
    "force"  : 15,
    "parry"  :-10,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "������䷨�ſ�",
    "action" : "$N���β�������ǰ�������������ϱ���һ��"BLINK""HIR"��������䷨�ſ���"NOR"��\n"
    "����$w��ǰ�·��̣�һ��ָ��$n",
    "dodge" : -10,
    "damage" : 20,
    "force"  : 20,
    "parry"  :-15,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "��������������",
    "action" : "$N�����ǰ���ŵ���������$wͻ��ǰ�̣���ת�����\n"
    "ʹ��һʽ"BLINK""HIR"���������������ס�"NOR"��������ƥ����й��$n",
    "dodge" : -5,
    "damage" : 25,
    "force"  : 25,
    "parry"  :-15,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "������������",
    "action" : "$Nƽ��бϴ����Բ��ֱ��˫�Ž��满������������$wʹ��һʽ"BLINK""HIR"����������������"NOR"��"
    "����������ת�������಻������$n",
    "dodge" : -5,
    "damage" : 35,
    "force"  : 35,
    "parry"  :-15,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "�˵³�����
����",
    "action" : "$N����̧�ۣ�����ǰ����Ϸ������ͦ����ƽ��������ǰ������$wʹ��\n"
    "һʽ"BLINK""HIR"���˵³��������桹"NOR"����$n",
    "dodge" : -10,
    "damage" : 30,
    "force"  : 30,
    "parry"  :-10,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "������������̦",
    "action" : "$N���ϲ����������أ�����$wһʽ"BLINK""HIR"��������������̦��"NOR"��"
    "����Բ�󣬴���$n",
    "dodge" : 0,
    "parry"  :-15,
    "damage" :30,
    "force"  :30,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "ֻ������Ӣ��",
    "action" : "$N�����˲������ֽ�ָ��ת������$wһ��"BLINK""HIR"��ֻ������Ӣ����"NOR"��"
    "��������ָ��$n",
    "dodge" : -10,
    "damage" : 40,
    "force"  : 40,
    "parry"  :-15,
    "lvl" : 0,
    "damage_type" : "����"
]),
([      "name":   "����ǰ�̽�ʥ̥",
    "action" : "$N�鲽�������ὣ�ؽ��������ϱ���һ��"BLINK""HIR"������ǰ�̽�ʥ̥��"NOR"ֱȡ$n",
    "dodge" : -5,
    "damage" : 40,
    "force"  : 40,
    "parry"  :-25,
    "lvl" : 0,
    "damage_type" : "����"
]),

});
int valid_enable(string usage) { 
    return (usage == "sword") || (usage == "parry");
}
int valid_learn(object me)
{
    if ((int)me->query("force") < 100)
   return notify_fail("�������������\n");
    if ((int)me->query_skill("force", 1) < 10)
   return notify_fail("����ڹ����̫ǳ��\n");
    return 1;
}
mapping query_action(object me, object weapon)
{
        //int i;
        //i=me->query("zhentian");
        //if( !me->query("zhentian") ) {
        return action[random(sizeof(action))];
        //}else {
        //return action[i];
        //}
}        
int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return notify_fail("�����������������û�а취��ϰ�⹳������\n");
        me->add("kee", -30);
        me->add("force", -3);
        write(HIC"������������죬���ǧ��ֻ��Ȼ��\n"NOR,me);
        return 1;
}
string perform_action_file(string func) {
  return CLASS_D("kunlun") + "/wugou-jian/" + func;
}
