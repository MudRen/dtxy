//huntian-jian
//lestat modi for dtxy 2001
inherit SKILL;
#include <ansi.h>
string* skill_head =({
        "$N�������ˣ�ʹ��һ��",
        "$N���쳤Ц����Ҳ������һ��",
        "$N����һԾ��ʹ�˸�",
        "$N��̬���У�һ��",
        "$N����ת����ͣ��ͻȻһ��",
        "$N����̤�˸����ǲ���һ��",
});
string* skill_tail =({
        "������$w����������$n����һն",
        "������$w��׼$n��$l���һն",
        "�����ֽ�$w��׼$n$lһ����ȥ",
        "������$w����ػ���$n��$l",
        "�����ֶ�׼$n$lһ����ȥ",
        "����$nת��֮�ʣ��ӳ�һ��",
});

mapping *action =
({
([
"action" : 
"$Nʹһʽ"+HIY"��������Զ�ȡ�"NOR+"��ǰ��̤��������$wһ��������
����������$n��$l",
"dodge"  : -5,
"damage" : 20,
"parry"  : 5,
"force"         : 100,
"skill_name"  : "��������Զ�ȡ�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"��ɱ�����ڷ���"NOR+"����¶ɱ��������$w
�Ӵ�����˷�����$n��$l",
"dodge"  : -10,
"damage" : 15,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "��ɱ�����ڷ���",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"����ǹ���ѩ��"NOR+"������$w��ʱ�ó�
���⽣Ӱ������$n��$l",
"dodge"  : -10,
"damage" : 20,
"parry"  : -20,
"force"         : 100,
"skill_name"  : "����ǹ���ѩ��",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"������ƶ�˪��"NOR+"������һ�Σ����Ӷ��ϣ�����$w
����һ������׼$n��$l��������",
"dodge"  : 10,
"damage" : 25,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "������ƶ�˪��",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"���������Ұ��"NOR+"�����˶�������$n��
����$w���Ȼ��������$n��$l��ȥ",
"dodge"  : 10,
"damage" : 20,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "���������Ұ��",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"��������ɣ��"NOR+"��һ����������$w����б����
��ֱָ$n��$l",
"dodge"  : -20,
"damage" : 30,
"parry"  : 10,
"force"         : 100,
"skill_name"  : "��������ɣ��",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"���󶷴����"NOR+"��΢΢һ��ת������$wȴ����
���´���������$n��$l",
"dodge"  : -20,
"damage" : 30,
"parry"  : 10,
"force"         : 100,
"skill_name"  : "���󶷴����",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"��ʱ���������"NOR+"������������£�����$w��ƥ����
����$n��$l",
"dodge"  : -10,
"damage" : 20,
"parry"  : 5,
"force"         : 100,
"skill_name"  : "��ʱ���������",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"�����������꡻"NOR+"������ͻ�䣬��������$w�籩������
��ĵ���$n��$l��ȥ",
"dodge"  : 10,
"damage" : 20,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "�����������꡻",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"�������Ʊ��ǡ�"NOR+"�������Ծ������$w�ڰ�������£�
����һ����ɫ��������$n��$l",
"dodge"  : 20,
"damage" : 20,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "�������Ʊ��ǡ�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"�������̿ա�"NOR+"��һƬ����֮��������$w���ּ���
��������ৡ���һ����$n��$l��ȥ",
"dodge"  : -5,
"damage" : 20,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "�������̿ա�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"����������硻"NOR+"����ؼ���һ�����ֳ�ǰ����������
$w��Ϊ�⻡��$n��$l��ȥ",
"dodge"  : -10,
"damage" : 30,
"parry"  : 5,
"force"         : 100,
"skill_name"  : "����������硻",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"��ҹ��������"NOR+"�������չ���Ӱ���д��£�˫��
����$w�����Ʊ��˵ش���$n��$l",
"dodge"  : -5,
"damage" : 20,
"parry"  : -10,
"force"         : 100,
"skill_name"  : "��ҹ��������",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIY"���������ӹ桻"NOR+"������$w���͡���һ��б������գ�
�漴���¡��ৡ����£�����һ�����֣���$n��$l��ȥ",
"dodge"  : -10,
"damage" : 30,
"parry"  : 5,
"force"         : 100,
"skill_name"  : "���������ӹ桻",
"damage_type" : "����",
]),
});

int valid_enable(string usage) {
    return usage == "sword" || usage == "parry";
}

int valid_learn(object me) {
if( (string)me->query_skill_mapped("force")!= "xuanzong-force")
        return notify_fail("��������ķ�Ϊ��ǳ��û��ѧ����һ����\n");
    if ((int)me->query_skill("kaitian-zhang", 1) < 40)
        return notify_fail("����һ��������ϻ��翪���Ʋſ��Խ�����\n");
    return 1;
}

mapping query_action(object me, object weapon)
{
mapping* m_actions;
m_actions=me->query("skill_huntian-jian");
if(me->query("skill_huntian-jian")==0 )
return action[random(sizeof(action))];
if( random(4) == 1 )
return m_actions[random(sizeof(m_actions))];
else
return action[random(sizeof(action))];
}

int practice_skill(object me) {
    object weapon;
    if (!objectp(weapon = me->query_temp("weapon")) ||
        (string)(weapon->query("skill_type")) != "sword")
        return notify_fail("����ɣ�����û��Ҳ�����䣿 :)\n");
       if ((int)(me->query("kee")) < 50)
        return notify_fail("���Ѿ���ƣ���ߣ�û��������ȥ����\n");
    me->receive_damage("kee", 30);
        write(HIB"�������������,����ɽǰ��������\n"NOR);
    return 1;
}

string perform_action_file(string action)
{
        return CLASS_D("kunlun") + "/huntian-jian/" + action;
}

void skill_improved(object me)
{
   int m_skill=me->query_skill("huntian-jian",1);

   if(m_skill>200&&m_skill%10==0){
     tell_object(me,HIW"��Ի���һ������������ˣ���Ļ���һ��������һ���µľ��磡\n"NOR);
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
     tell_object(me,HIW"��ͻȻ�������飬�Ի���һ���������һ���µ��÷���\n"NOR);
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

   m_actions=me->query("skill_huntian-jian");
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
//   if(!arg||arg==" ")arg="����һ����ɱ��"+chinese_number(sizeof(m_actions)+1);
   m_act+=(["name":arg]);
   msg= skill_head[random(sizeof(skill_head))]+BLINK+HIM"��"+arg+"��"NOR
                 +skill_tail[random(sizeof(skill_tail))];
   m_act+=(["action":msg]);
   m_actions+=({m_act});
   me->set("skill_huntian-jian",m_actions);
   me->add("zichuang/times",1);
}

