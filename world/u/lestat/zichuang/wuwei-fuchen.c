// wuwei-fuchen��Ϊ����
// /daemon/skill/wuwei-fuchen.c
// writted by mind 2001/2
//lestat modi for dtxy 2001

#include <ansi.h>

inherit SKILL;
string* skill_head =({
        "$N�������ˣ�ʹ��һ��",
        "$N�������ܣ�һʽ",
        "$Nʹ��",
        "$N��¶΢Ц��һʽ",
        "$Nһ����ת��ʹ��",
});
string* skill_tail =({
        "������$w��Ϊһ���������$n��$l��",
        "������$w��Ϊһ���������$n��",
        "������$w��ƫһ�ᣬֱ��$n��$l��",
        "������$w��ɣ�������㺮�⡣",
        "����ʱһ������Ʈ��$n",
});
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
        if (random(me->query_str()) >= 30 && me->query_skill("wuwei-fuchen",1) > 100 &&
             me->query_skill("parry",1) > 100 &&
             me->query("force") > 1000 &&
             me->query("kee")>300) {
                me->add("kee",-10);           
                me->add("force", -30);
                return ([
                "action": HIR "$N����һ�������������$w"+HIR"������º�$n"+HIR"����һ��һ����ɽ�������ھ�����Ϣ����$n"+HIR"�ؿ�ײȥ��"NOR,
                "force": 60,
                "dodge": -85,
                "parry": -85,
                "damage" : 70,
                "damage_type": "����"]);
        }
           if (random(me->query_str()) >= 28 && me->query_skill("wuwei-fuchen",1)> 150 &&
                me->query_skill("parry",1) > 150 &&
                me->query("force") > 1500 &&
                me->query("kee")>500) {
                me->add("kee",-20);            
                me->add("force", -50);
                return ([
                "action": HIR "$N������$w"+HIR"������Ȧ������$n"+HIR"ԽתԽ����ԽתԽ�죬$n"+HIR"��ʱ�����������׵���ת�˼����ۿ���Ҫˤ����"NOR,
                "force": 120,
                "dodge": -35,
                "parry": -35,
                "damage" : 100,
                "damage_type": "����"]);
        }
      
       return action[random(sizeof(action))];
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
void skill_improved(object me)
{
   int m_skill=me->query_skill("wuwei-wuchen",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"�����Ϊ��������������ˣ������Ϊ����������һ���µľ��磡\n"NOR);
     if(me->query("zichuang/times")>7){
        tell_object(me,HIW"Ȼ����Ĺ����Ѿ��������壬�����ٴ��������ˡ�\n"NOR);
        return;
     }
     if(random(me->query("kar"))<20){
        tell_object(me,HIW"Ȼ��������о�Ȼ������һ��ʧ��У�\n"NOR);
        return;
     }
     if((random(me->query("int")/2)+(int)me->query_skill("literate")/50)<10){
       tell_object(me,HIW"Ȼ�������������һ�����ĸо����·���һ˿��Ҫ�Ķ���û��ץס��\n"NOR);
       return;
     }
     tell_object(me,HIW"��ͻȻ�������飬����Ϊ�����������һ���µ��÷���\n"NOR);
     tell_object(me,"��Ϊ����ȡһ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
   }
   return;
}

void name_skill(object me, string arg)
{
	string *banned_name = ({
                "��", "��", "��", "��", "��", "��", "��", "��",
                "ү", "��", "��ʦ", "����", "����",
        });
   mapping* m_actions;
   mapping m_act=([]);
   int content, i=strlen(arg);
   string msg;

   m_actions=me->query("skill_wuwei-wuchen");
   if(!pointerp(m_actions))m_actions=({});

   content=me->query("str")+2*me->query_skill("unarmed",1)/10;
   m_act+=(["damage":content]);
   content=-me->query("spi");
   m_act+=(["dodge" :content]);
   content=-me->query("cps");
   m_act+=(["parry" :content]);
   content=me->query("con")+2*me->query_skill("force",1)/10;
   m_act+=(["force" :content]);
   m_act+=(["damage_type":"����"]);
if (!arg || arg=="") 
     {
          tell_object(me,"��Ϊ�������ʽȡһ�����֣�");
          input_to( (: call_other, __FILE__, "name_skill", me:));
          return;
     }
     else while(i--) 
     {
                if( arg[i]<=' ' ) 
                {
                        tell_object(me,"��ʽ���ֲ���ʹ�ÿ�����Ԫ���������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if(strsrch(arg, "��") >= 0) 
                {
                        tell_object(me,"��ʽ���ֲ����пո��������趨һ�����֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
                if( i%2==0 && !is_chinese(arg[i..<0]) ) 
                {
                        tell_object(me,"�����á����ġ�Ϊ�������ʽȡ���֣�");
                        input_to( (: call_other, __FILE__, "name_skill", me:));
                        return;
                }
     }
     if( member_array(arg, banned_name)!=-1 ) 
     {
     tell_object(me,"�Բ����������ֻ���������˵����š��������趨һ�����֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
     if( (strlen(arg) < 8) || (strlen(arg) > 16 ) ) 
     {
     tell_object(me,"�Բ�����ʽ���ֱ����� �� �� �� �������֣�");
     input_to( (: call_other, __FILE__, "name_skill", me:));
     return;
     }
//   if(!arg||arg==" ")arg="��Ϊ������ɱ��"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIM"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_wuwei-wuchen",m_actions);
    me->add("zichuang/times",1);
}


