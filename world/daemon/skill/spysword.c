// spysword. ���̿ͽ�����
// /daemon/skill/spysword.c
// writted by mind 2001/2

#include <ansi.h>
inherit SKILL;
string* skill_head =({
        "$N����������������˼,��Ȼ�б�",
        "$Nб�г�������Х����ȴ�����˿�ɬ����ζ��һ��",
        "$N���Ƿ��裬�����滺���裬ʹ��",
        "$N΢��˫Ŀ��һ����į�����鲼�����ϣ�һʽ",
        "$N���첻������ӹ�һ˿�ǳʹ��",
});
string* skill_tail =({
        "������$w��Ϊһ���������$n��$l",
        "������$wңң����$n��$l",
        "������$w�ɴ�$n��$l",
        "������$w��ɣ�������㺮��",
        "����ʱһ������Ʈ��$n",
});
mapping *action = ({
      ([        "action":
"$Nһ����̾��$w���һ��"+HIG"�����Ĵ���ϧ���㡹"NOR+"����$n��$l���̶�ȥ",

                 "dodge": -35,
                 "parry": -5,
                 "damage": 60,
                 "damage_type": "����"
       ]),
        ([      "action":
"$N����üͷ���������к����Թ��$wһ��������һ��"+MAG"���콫��������"NOR+"����$n��$l",
 
                 "dodge": 0,
                "parry" : -10,
                 "damage": 55,
                "damage_type": "����"
         ]),
         ([      "action":
"$N���첻������ӹ�һ˿�ǳ$w�ݻ���һ��"+HIC"������˼��"NOR+
"ңң����$n��$l",

                "dodge": 0,
                "parry": -5,
                "damage": 70,
                "damage_type": "����"
          ]),
          ([      "action":
"$N����������������˼,��Ȼ���У�\n"
"��Ȼ�����ϯ��������������$n��$l,��һ��"+RED"��ŭ���񻨡�"NOR,

                "dodge": 0,
                "parry": -30,
                "damage": 50,
                 "damage_type": "����"
           ]),
           ([      "action":
"$N���Ƿ��裬�����滺���裬�������\n"
"һ��"+MAG"�������죬ˮãã��"NOR+"��$w����$n��$l",
 
                  "damage": 80,
                 "dodge": -40,
                "parry": 0,
                 "damage_type": "����"
           ]),
           ([      "action":
"$N΢��˫Ŀ��һ����į�����鲼�����ϣ���������,������ʱѹ������\n"
"һ��"+BLU"����į��������ʪ��"NOR+"�ɴ�$n��$l",
                  "dodge": 0,
                "parry": -50,
                  "damage": 60,
                  "damage_type": "����"
           ]),
           ([      "action":
"$Nб�г�������Х����ȴ�����˿�ɬ����ζ��$w�����·��̶���\n"
"һ��"+HIM"����˼������ƾ�"NOR+"����$n��$l",
                   "dodge": 0,
                "parry": -15,
                   "damage": 65,
                   "damage_type": "����"
             ]),
             ([      "action":
"$N����ҡͷ��˫Ŀ�������������$w��ӳ�Ų԰׵Ĺ�â\n"
"�������ֵ����ֶ���,һ��"+YEL"��Ī�򻨼�����С�"NOR+"����$n��$l",
                  "dodge": 0,
                "parry": -5,
                  "damage": 80,
                  "damage_type": "����"
              ]),
              (["action":               HIW"$N���е�$w"+HIW"��һ��ָ������$n"+HIW"��$l��������"NOR,
                "dodge":                -10,
                "parry" :               -50,
                "damage" :              50,
                "damage_type":  "����"
                ]),
                (["action":             HIW"$N����һת�����е�$w"+HIW"����������$n"+HIW"��$l���˹�ȥ"NOR,
                "dodge":                -10,
                "parry" :               -60,
                "damage":               60,
                "damage_type":  "����"
                ]),
                (["action":             HIW"$N����һ����$w"+HIW"Ю�������������$n"+HIW"��$l"NOR,
                "dodge":                -10,
                "parry" :               -70,
                "damage" :              70,
                "damage_type":  "����"
                ]),
                (["action":             HIW"$N����һ�������е�$w"+HIW"�������ϴ���$n"+HIW"��$l"NOR,
                "dodge":                -10,
                "parry" :               -80,
                "damage":               80,
                "damage_type":  "����"
                ]),
                (["action":             HIW"$N����$w"+HIW"���Ⱪ������ǧ����Ы��$n"+HIW"$lҧȥ"NOR,
                "dodge":                -10,
                "parry" :               -90,
                "damage":               90,
                "damage_type":  "����"
                ]),
                (["action":             HIW"$N���е�$w"+HIW"���޷����ݵ��ٶ�ֱ��$n"+HIW"��$l"NOR,
                "dodge":                -10,
                "parry" :               -100,
                "damage":               100,
                "damage_type":  "����"
                ]),
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 200 )
        return notify_fail("�������������û�а취���̿ͽ�����\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

        return 1;
}

int valid_enable(string usage)
{
        return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
     int i;
     mapping* m_actions;
     m_actions=me->query("skill_spysword");
     i=me->query("dunnoname");
     if( !me->query("dunnoname") ) 
     {
     	if(me->query("skill_spysword")==0 )
     		return action[random(8)];
     	if( random(3) == 1 )
     		return m_actions[random(sizeof(m_actions))];
     	else
        	return action[random(8)];
      }
      else 
      {
        	return action[i];
      }
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return 
notify_fail("�����������������û�а취��ϰ�̿ͽ�����\n");
        me->receive_damage("kee", 30);
        me->add("force", -3);
          write("�㰴����ѧ����һ��̿ͽ�����\n");
        return 1;
}

string perform_action_file(string func)
{
return CLASS_D("sanxian") + "/spysword/" + func;
}
void skill_improved(object me)
{
   int m_skill=me->query_skill("spysword",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"��Դ̿ͽ�������������ˣ���Ĵ̿ͽ���������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�Դ̿ͽ����������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_spysword");
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
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIM"��"+arg+"��"NOR
                  +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_spysword",m_actions);
    me->add("zichuang/times",1);
}


