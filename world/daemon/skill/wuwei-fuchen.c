// wuwei-fuchen��Ϊ����
// /daemon/skill/wuwei-fuchen.c
// writted by mind 2001/2
//lestat modi for dtxy 2001

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([ "action": "$N����������紵�ͣ�ƮȻ������һ��"+HIM"�����Χ����"NOR+"������$w���һ����ԲȦ������$n�����䡣",
   "dodge": -5,
   "damage":30,
   "parry": -5,
   "skill_name" : "���Χ��",
   "damage_type":  "����"
]),
([ "action": "$N��ָ��$w��һ������$w����֮��һ��"+HIG"��ӹ�����š�"NOR+"������հ�����$n��$l",
   "dodge": -10,
   "damage":50,
   "parry": -10,
   "skill_name" : "ӹ������",
   "damage_type":  "����"
]),
([ "action": "$N������ע��$w�����ʹ��һʽ"+HIY"������Ǭ��"NOR+"��$w��ز���裬ֱ�������ƿ�һ�����$n",
   "dodge": -40,
   "damage":40,
   "parry": 0,
   "skill_name" : "����Ǭ��",
   "damage_type":  "����"
]),
([ "action": "$Nһ���ߺȣ�����������һʽ"+HIC"������Ϊ��"NOR+"��$w����ת������Ӱ�ݺᣬֱ����Բ��Բ����ֱ�������ƻã�����$n",
   "dodge": -10,
   "damage":40,
   "parry": -50,
   "skill_name" : "����Ϊ",
   "damage_type":  "����"
]),
([ "action": "$N��¶΢Ц��ǰһ��������$w�������ʹ��һʽ"+HIW"����ֹ��ֹ��"NOR+"������ƽ������������˿������",
   "dodge": -20,
   "damage":30,
   "parry": -30,
   "skill_name" : "��ֹ��ֹ",
   "damage_type":  "����"
]),
});
int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( (int)me->query("max_force") < 100 )
               return notify_fail("����������㡣\n");

       if ((int)me->query_skill("force") < 30)
               return notify_fail("����ڹ����̫ǳ��\n");

       if ( !objectp(weapon = me->query_temp("weapon"))
       || ( string)weapon->query("skill_type") != "whip" )
               return notify_fail("���������һ�����Ӳ�������Ϊ������\n");

       return 1;
}


mapping query_action(object me)
{   
	mapping* m_actions;
     m_actions=me->query("skill_wuwei-fuchen"); 
        if (random(me->query_str()) >= 30 && me->query_skill("wuwei-fuchen",1) > 100 &&
             me->query_skill("parry",1) > 100 &&
             me->query("force") > 1000 &&
             me->query("kee")>300 &&
             (string)me->query("family/family_name")=="����ɢ��") {
                me->add("kee",-10);           
                me->add("force", -30);
                return ([
                "action": HIR "$N����һ�������������$w"+HIR"������º�$n"+HIR"����һ��һ����ɽ�������ھ�����Ϣ����$n"+HIR"�ؿ�ײȥ"NOR,
                "force": 80,
                "dodge": -85,
                "parry": -85,
                "damage" : 80,
                "damage_type": "����"]);
        }
           if (random(me->query_str()) >= 40 && me->query_skill("wuwei-fuchen",1)> 150 &&
                me->query_skill("parry",1) > 150 &&
                me->query("force") > 1500 &&
                me->query("kee")>500 &&
                (string)me->query("family/family_name")=="����ɢ��") {
                me->add("kee",-20);            
                me->add("force", -50);
                return ([
                "action": HIR "$N������$w"+HIR"������Ȧ������$n"+HIR"ԽתԽ����ԽתԽ�죬$n"+HIR"��ʱ�����������׵���ת�˼����ۿ���Ҫˤ��"NOR,
                "force": 120,
                "dodge": -60,
                "parry": -60,
                "damage" : 120,
                "damage_type": "����"]);
        }
     //if( me->query("skill_wuwei-fuchen")==0 )
     return action[random(sizeof(action))];
     /*if( random(4) == 1 )
     return m_actions[random(sizeof(m_actions))];
     else
     return action[random(sizeof(action))];*/
}

int practice_skill(object me)
{
       object weapon;

       if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "whip")
               return notify_fail("��ʹ�õ��������ԡ�\n");
       if ((int)me->query_skill("force") < 100)
               return notify_fail("����ڹ����̫ǳ��\n");
       if ((int)me->query("kee") < 50)
               return notify_fail("���������������Ϊ������\n");
       me->receive_damage("kee", 15);
       return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        weap = victim->query_temp("weapon");
                weap1 = me->query_temp("weapon");
		if( me->query_temp("icefire") || victim->query_temp("icefire") )
			return 1;
		if(( string)me->query("family/family_name") != "����ɢ��" )
			return 1;
                if( (me->query_skill("wuwei-fuchen") > 60) && (me->query("force") > 100)
                         && (victim->query_temp("weapon")) 
                         && random(10)>5)
                 {
                        message_vision(HIY "ֻ��$N���ٻ���" + weap1->name() + "��ת����������СȦ�ӣ�������֮����ס�Է���" + weap->name() +"��\n" NOR, me );
                        victim->start_busy(2+random(2));
                        if (random(me->query_str()) > victim->query_str()/2 )
                        {       
                        message_vision(HIY "$N�����ֱ�����һק��" + weap->name() + "ȴ�޷���"+weap1->name()+"�Ĳ������ѿ����鼱֮��ֻ�÷��������еı��С�\n" NOR, victim );
                        weap->move(environment(me));
                        victim->reset_action();
                        } else {
                        message_vision(HIY "$N�����ɾ���" + weap->name() + "˳�ŷ��������ת���£��⿪��"+weap1->name()+"�Ĳ��ơ�\n" NOR, victim );
                        victim->add("force",-50);
                        }
                        me->add("force", -50);
                 }
                 return 1;
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/wuwei-fuchen/" + func;
}


