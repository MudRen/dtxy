// bingpo-hand.c ���ǵ�
// /daemon/skill/bingpo-hand.c
// writted by mind 2001/2


inherit SKILL;
#include <ansi.h>
mapping *action = ({
([  "action": "$N˫��һ��һ��"+HIW"��˪�����ء�"NOR+"������ɨ��$n��$l",
    "dodge": 30,
    "parry": -10,
    "force": 100,
    "damage_type": "����",
    "weapon" : "˫��",
]),
([  "action": "$Nһ��"+HIW"����ѩ�����ݡ�"NOR+"������ͻȻ��ת��������$n��˫������$n��$l", 
    "dodge": 20,
    "force": 150,
    "parry": 10,
    "damage_type": "����",
    "weapon" : "˫��",
]),
([  "action": "$N�������������֣�һ��"+HIW"�������ëѩ��"NOR+"��Ѹ���ޱȵ�ץ��$n��$l",   
    "dodge": 50,
    "force": 200,
    "parry": -40,
    "damage_type": "ץ��",
    "weapon": "������ָ",
]),
([  "action": "$N����һ����ͻȻһ��"+HIW"������ǧ�"NOR+"����Ю�溮֮������$n��$l",   
    "dodge": 60,
    "force": 250,
    "damage_type": "����",
    "weapon": "������",
]),
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }   

mapping query_action(object me)
{
   if (random(me->query_skill("unarmed",1)) > 60 &&
   me->query_skill("force",1) > 50 &&
   me->query("force") > 100 ) {
   me->add("force", -100);
   return ([
   "action": "$N����Ԫ������͸����һʽ"+HIW"������˪�꡻"NOR+"�������ޱȵػ���$n",
   "force": 400,
   "damage_type": "ײ��",
   "weapon": "ȫ��",]);
    }
    return action[random(sizeof(action))];
}

int valid_learn(object me)
{
    if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
   return notify_fail("�����ǵ�������֡�\n");
    
    if ((int)me->query("max_force") < 200)
   return notify_fail("�������̫�����޷������ǵ�");
    return 1;
}


int practice_skill(object me)
{
    if ((int)me->query("kee") < 30)
   return notify_fail("�������̫���ˣ�����Ϣһ�°ɡ�\n");
    if ((int)me->query("force") < 30)
   return notify_fail("����������������ǵ���\n");
    
   me->receive_damage("kee", 30);
    me->add("force", -20);
    write(HIC"˫�Ʒ��������ĺ��⡣\n"NOR);
    return 1;
}

void skill_improved(object me)
{
        if( (int)me->query_skill("bingpo-hand", 1)  % 10 == 0 ) {
                tell_object(me,
                        HIC "\n��ͻȻ�����ľ����壬ɱ������....\n\n" NOR);
                me->add("bellicosity", -random( (int)me->query_kar() * 10));
                if ((int)me->query("bellicosity") < 0 ) me->set("bellicosity", 0);
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
return CLASS_D("sanxian") + "/bingpo-hand/" + func;
}
