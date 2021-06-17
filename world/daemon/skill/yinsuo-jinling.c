//��������
inherit SKILL;
#include <ansi.h>;

string* skill_head =({
        "$N�������ˣ�ʹ��һ��",
        "$N�������ܣ�һʽ",
        "$N����һ�ϣ�ʹ��",
        "$N��ȻһЦ��һʽ",
        "$N����Ծ��ʹ��",
});
string* skill_tail =({
        "������$w��Ϊһ���������$n��$l��",
        "������$w��������Ӱ����$n��",
        "������$w��ƫһ�ᣬֱ��$n��$l��",
        "������$w��ɣ�������㺮�⡣",
        "��$w���Ҽ缱˦��󣬶��ػ���$n$l��",
});

mapping *action = ({
   ([   "action":
"$nֻ����ǰһ�����ƺ�����$N����һ�ϣ����漴�ּ�$N�ص�ԭ�أ�ȴ�ƴ�δ�뿪��һ��"+HIM"�����ϡ�"NOR"����Ȼ����$n�ĺ���",
     "dodge":     -5,
                "parry":                -10,
     "damage":     40,
     "damage_type":   "����"
   ]),
   ([   "action":
"����Ծ��$ņ��һ����������$N����$w��������Ӱ��"+HIC"[����]"NOR"�ѽ�$n����",
     "dodge":     -15,
                "parry":                -25,
     "damage":     40,
     "damage_type":   "����"
   ]),
   ([   "action":
"$N����$w����һ��������$w�����һ��,һʽ"+HIG"[����]"NOR"���εĴ���$n������",
     "dodge":     -10,
                "parry":                -15,
     "damage":     35,
     "damage_type":   "����"
   ]),
   ([   "action":
"$N���е�$w����һ����˿������û������������Ӻ����������������ˣ���$n����Ʈ������������һ��"+HIW"[����]"NOR"",
     "dodge":     -10,
                "parry":                -5,
     "damage":     50,
     "damage_type":   "����"
   ]),
   ([   "action":
"ͻȻ֮�䣬$N����һ��һ�Σ��������ɣ�ʹ��һ��"+HIB"��֧�ϡ�"NOR"��$w���Ҽ缱˦��󣬶��ػ���$n$l����������������ʸ�ö���",
     "dodge":     -20,
                "parry":                -10,
     "damage":     45,
     "damage_type":   "����"
   ]),
});

int valid_learn(object me)
{
   object ob;
//if( (string)me->query("gender") !="Ů��")
//return notify_fail("��������ֻ��Ů�Ӳ���ѧϰ!!\n");
   if( (int)me->query("max_force") < 50 )
     return notify_fail("�������������û�а취���������塣\n");

   if( (string)me->query_skill_mapped("force")!= "jiuyin-xinjing")
     return notify_fail("����������������˿���ľ����ľ���������\n");

   if( !(ob = me->query_temp("weapon"))
   ||   (string)ob->query("skill_type") != "whip" )
     return notify_fail("���������һ�ѱ��Ӳ������޷���\n");

   return 1;
}

int valid_enable(string usage)
{
   return usage=="whip" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
	mapping* m_actions;
	if(me->query("skill_yinsuo-jinling")==0) return action[random(5)];
	if(random(2))return action[random(5)];
	m_actions=me->query("skill_yinsuo-jinling");
	return m_actions[random(sizeof(m_actions))];
}

int practice_skill(object me)
{
   if( (int)me->query("kee") < 30
   ||   (int)me->query("force") < 3 )
     return notify_fail("�����������������û�а취��ϰ�������塣\n");
   me->receive_damage("kee", 30);
   me->add("force", -3);
   write("�㰴����ѧ����һ���������塣\n");
   return 1;
}


string perform_action_file(string func)
{
return CLASS_D("pansi") + "/yinsuo-jinling/" + func;
}


void skill_improved(object me)
{
   int m_skill=me->query_skill("yinsuo-jinling",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"��������������������ˣ�����������������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�����������������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_yinsuo-jinling");
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
//   if(!arg||arg==" ")arg="���������ɱ��"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIR"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_yinsuo-jinling",m_actions);
   me->add("zichuang/times",1);
}
 
