
//���彣��    
//lestat modi for dtxy 2001

inherit SKILL;
#include <ansi.h>

string* skill_head =({
        "$N����һ�ˣ�̤�������Ǭ�ţ�ʹ��һ��",
        "$N����һ�Σ�ͻȻ֮��ת�������ţ�����һ��",
        "$N���ż��������Կ����룬�����������ţ�����һ������������ʹ��",
        "$N����б�ɣ����뿲��ͻȻʹ��",
        "$N���˷�������������֮��һ��",
        "$N������̤���ţ���������һ��",
});

string* skill_tail =({
        "������$w����������$n����һն",
        "������$w��׼$n��$l���һն",
        "�����ֽ�$w��׼$n$lһ����ȥ",
        "������$w����ػ���$n��$l",
        "�����ֶ�׼$n$lһ����ȥ",
        "����$nת��֮�ʣ��ӳ�һ��",
});



mapping *action = ({
   ([   "action":     "$Nʹ��һ��"+HIR"���Ǻ�Ӱ����"NOR+"��������˸�������������޵ش���$n$l",
     "dodge":     -10,
     "parry":     -15,
     "damage":     35,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N����ת����ͣ��ͻȻһ��"+HIY"��һ����Ϭ��"NOR+"ʹ��������$w����һ������������$n$l",
     "dodge":     -10,
     "parry":     -15,
     "damage":     45,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N����̤�˸����ǲ���һ��"+HIM"���ŵ����硹"NOR+"����$w����������$n����һն",
     "dodge":     -5,
     "parry":     -15,
     "damage":     40,
     "damage_type":   "����"
   ]),
   ([   "action":     "����$N���˼�������Ȼ������Ծ������$wһʽ"+HIW"���׺�������"NOR+"��׼$n��$l���һն",
     "dodge":     -15,
     "parry":     -5,
     "damage":     50,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N����һԾ��ʹ�˸�"+HIB"���˷��ȥ��"NOR+"��ȴ��ת��֮�ʶ�׼$n$lбб�ӳ�һ��",
     "dodge":     -5,
     "parry":     -25,
     "damage":     35,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N��̬���У�����$wƾ��һָ��һ��"+HIC"������ǧ�ء�"NOR+"����ػ���$n��$l",
     "dodge":     -10,
     "parry":     -10,
     "damage":     40,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N����$w����һ�֣�ʹһ��"+HIG"������ͨ�ġ�"NOR+"���ֶ�׼$n$lһ����ȥ",
     "dodge":     -10,
     "parry":     -20,
     "damage":     35,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N������Ԫ�ݻ����徳��ʹ��"+MAG"������������"NOR+"$w���ŵ���ɫ�Ľ�â��$n$l��ȥ",
     "dodge":     -50,
     "parry":     -50,
     "damage":     100,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N��ʼ���ݻ����徳��ʹ��"+HIW"�����ͬ�١�"NOR+"$w��������ɫ�Ľ�â��$n$l��ȥ",
     "dodge":     -50,
     "parry":     -50,
     "damage":     100,
     "damage_type":   "����"
   ]),
   ([   "action":     "$N�������ݻ�̫�徳��ʹ��"+HIC"��������ơ�"NOR+"$w��������ɫ�Ľ�â��$n$l��ȥ",
     "dodge":     -50,
     "parry":     -50,
     "damage":     100,
     "damage_type":   "����"
   ]),
});

int valid_learn(object me)
{
   object ob;

   if( (int)me->query("max_force") < 50 )
     return notify_fail("�������������û�а취�����彣����\n");

   if( !(ob = me->query_temp("weapon"))
   ||   (string)ob->query("skill_type") != "sword" )
     return notify_fail("���������һ�ѽ�������������\n");

   return 1;
}

int valid_enable(string usage)
{
   return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
     	mapping* m_actions;
     	m_actions=me->query("skill_sanqing-jian");
     	if( !me->query_temp("sq_perform") )
     	{
     		if( m_actions && random(2) == 1 )
     			return m_actions[random(sizeof(m_actions))];
     		else 
    			return action[random(7)];
    	}
	else
		return action[me->query_temp("sq_perform")];
}

int practice_skill(object me)
{
   if( (int)me->query("kee") < 30
   ||   (int)me->query("force") < 3 )
     return notify_fail("�����������������û�а취��ϰ���彣����\n");
   me->receive_damage("kee", 30);
   me->add("force", -3);
   write("�㰴����ѧ����һ�����彣����\n");
   return 1;
}
string perform_action_file( string action)
{
return CLASS_D("zhenyuan") + "/sanqing-jian/" + action;
}


void skill_improved(object me)
{
   int m_skill=me->query_skill("sanqing-jian",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"������彣����������ˣ�������彣������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�����彣�������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_sanqing-jian");
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
//   if(!arg||arg==" ")arg="���彣����"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIW"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_sanqing-jian",m_actions);
   me->add("zichuang/times",1);
}
 

