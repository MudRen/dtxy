// chixin-jian.c
// �����鳤����
// Juney: 07/04/97: Genesis.
//lestat 2001 �޸�for��˿�����հ׷�
//�����鳤��Ϊ�׾�������

#include <ansi.h>
#include <combat.h>
inherit F_DBASE;
inherit SKILL;
string *xue_name = ({ 
HIR"�͹�Ѩ"NOR,HIR"����Ѩ"NOR,HIR"����Ѩ"NOR,
HIG"��ԪѨ"NOR,HIG"����Ѩ"NOR,HIG"�м�Ѩ"NOR,
HIY"�н�Ѩ"NOR,HIY"��ͻѨ"NOR,HIY"�ٻ�Ѩ"NOR,
HIM"����Ѩ"NOR,HIM"����Ѩ"NOR,HIM"���Ѩ"NOR,
HIW"�Ϲ�Ѩ"NOR,HIW"��ԨѨ"NOR,HIW"�쾮Ѩ"NOR,
HIC"��ȪѨ"NOR,HIC"����Ѩ"NOR,HIC"����Ѩ"NOR,}); 
string *baifa= ({
HIB"$N���ſھ�����Ͷ���չ���գ�ͻ�������������\n"NOR,
HIY"$N���ſھ�������ĺĺƵ˼�䣬ǧ��濾�ֻ�ǿա�\n"NOR,
CYN"$N���ſھ���������������飬ȴ���칫��������\n"NOR,
MAG"$N���ſھ��������޶���˼�࣬�˺������޾��ڡ�\n"NOR,
HIG"$N���ſھ�����Ȼ���������棬Ը�˳��ÿ��źޡ�\n"NOR,
HIW"$N���ſھ�������δ���ɰ�ͷ������������ǰԵ��\n"NOR,
HIM"$N���ſھ������鲻�Ƽ��Ƹ֣������칫�����ۡ�\n"NOR,
HIC"$N���ſھ����ճ��˻�����ʱ����������鳤����\n"NOR
});
mapping *action =
({
([
"action" : 
"$Nʹһʽ"+HIC"����Ͷ���չ���ա�"NOR+"����¶΢Ц������$wһ��������
����������$n��$l",
"dodge"  : -5,
"damage" : 20,
"parry"  : 5,
"skill_name"  : "����Ͷ���չ���ա�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"��ͻ�������������"NOR+"���������������ж��䣬����$w
��һ�����벻���ķ�λбб����$n��$l",
"dodge"  : -10,
"damage" : 15,
"parry"  : -10,
"skill_name"  : "��ͻ�������������",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"������ĺĺƵ˼�䡻"NOR+"���������ߣ����׸���Ƭ�̣���
������$w��Ȼ���ϣ�����$n��$l",
"dodge"  : -10,
"damage" : 20,
"parry"  : -20,
"skill_name"  : "������ĺĺƵ˼�䡻",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"��ǧ��濾�ֻ�ǿա�"NOR+"������һ�Σ����Ӷ��ϣ�����$w
����һ������׼$n��$l��������",
"dodge"  : 10,
"damage" : 25,
"parry"  : -10,
"skill_name"  : "��ǧ��濾�ֻ�ǿա�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"��������������须"NOR+"��һ����������$n����Ӱ���棬
����$w���Ȼ��������$n��$l��ȥ",
"dodge"  : 10,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "��������������须",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"��ȴ���칫��������"NOR+"��һ����������$w����б����
��ֱָ$n��$l",
"dodge"  : -20,
"damage" : 30,
"parry"  : 10,
"skill_name"  : "��ȴ���칫��������",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"�������޶���˼�ࡻ"NOR+"��΢΢һ��ת������$wȴ����
���´���������$n��$l",
"dodge"  : -20,
"damage" : 30,
"parry"  : 10,
"skill_name"  : "�������޶���˼�ࡻ",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"���˺������޾��ڡ�"NOR+"����ɫ΢�䣬���ж�Ȼ���������
�ȣ�����$w��ƥ��������$n��$l",
"dodge"  : -10,
"damage" : 20,
"parry"  : 5,
"skill_name"  : "���˺������޾��ڡ�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"����Ȼ���������桻"NOR+"���������ף�����̾�˿���������
Ө����������������$w�й�ֱ����Ѹ���ޱȵ���$n��$l��ȥ",
"dodge"  : 10,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "����Ȼ���������桻",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"��Ը�˳��ÿ��źޡ�"NOR+"�������Ծ������$w�ڰ�������£�
����һ����ɫ��������$n��$l",
"dodge"  : 20,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "��Ը�˳��ÿ��źޡ�",
"damage_type" : "����",
]),
([
"action" : "$Nʹһʽ"+HIC"������δ���ɰ�ͷ��"NOR+"������ಽ������$w���ּ���������
��ৡ���һ����$n��$l��ȥ",
"dodge"  : -5,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "������δ���ɰ�ͷ��",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"������������ǰԵ��"NOR+"����ؼ���һ�����ֳ�ǰ����������
$w��Ϊ�⻡��$n��$l��ȥ",
"dodge"  : -10,
"damage" : 30,
"parry"  : 5,
"skill_name"  : "������������ǰԵ��",
"damage_type" : "����",
]),
([
"action" : "$Nʹһʽ"+HIC"�����鲻�Ƽ��Ƹ֡�"NOR+"������Ծ�𣬲�����Ӱ������ȴ�ִ�
����д��£�˫������$w�����Ʊ��˵ش���$n��$l",
"dodge"  : -5,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "�����鲻�Ƽ��Ƹ֡�",
"damage_type" : "����",
]),
([
"action" : 
"$Nʹһʽ"+HIC"�������칫�����ۡ�"NOR+"������$w���͡���һ��б������գ�
�漴���¡��ৡ����£�����һ�����֣���$n��$l��ȥ",
"dodge"  : -10,
"damage" : 30,
"parry"  : 5,
"skill_name"  : "�������칫�����ۡ�",
"damage_type" : "����",
]),
([
"action" : "$Nʹһʽ"+HIC"���ճ��˻�����ʱ��"NOR+"������΢̧������$w���·�����
����һ�ɾ��練��$n��$l",
"dodge"  : -5,
"damage" : 20,
"parry"  : -10,
"skill_name"  : "���ճ��˻�����ʱ��",
"damage_type" : "����",
]),
([
"action" : 
"$N�㾡ȫ�����"+HIC"����������鳤����"NOR+"����ɫʮ�ּ�������������
����������$w���費ͣ��ȫ�������������˵Ľ����У�$n���ɺ�Ȼ��ֻ��$N
����΢�䣬�����������ѱ���$n��$l",
"dodge"  : -10,
"damage" : 50,
"parry"  : -25,
"skill_name"  : "����������鳤����",
"damage_type" : "����",
]),
});

int valid_enable(string usage) {
    return usage == "sword" || usage == "parry";
}

int valid_learn(object me) {
    if ((int)me->query_skill("jiuyin-xinjing",1) < 20 )
	return notify_fail("��ľ����ķ�Ϊ��ǳ��û��ѧ�����鳤����\n");
    if ((int)me->query_skill("yueying-wubu", 1) < 20)
        return notify_fail("�����Ӱ�貽��Ϊ��ǳ��û��ѧ�����鳤����\n");
    return 1;
}

mapping *action_baifa =
({
([
"action" : 
RED"$Nʮָ��Ⲧ�����ң���Ūһ������Ի��"+HIG"�������ɡ�"+NOR+RED"������������������Σ�һ˿˿"+NOR+HIW"�׷�"+NOR+RED"������ٺ�Ϯ��"NOR,
"parry_msg" :
"$n����̴�壬��ת��������ϣ���¥����һ��"+HIB"��Ե��������"+NOR"��$Nֻ���ĵߵ��黳�������ֶ�����ϴ��������",
"parry_power":		10,
"dodge"  : -10,
"parry" : -10,
"force" : 100,
"skill_name"  : "������",
"damage_type" : "����",
]),
([
"action" : 
RED"$N�������ң�һ��"+NOR+HIM"������¥��"+NOR+RED"��$N"+NOR+HIW"�׷�"+NOR+RED"������������裬�����һ���죬����"+NOR+HIW"�׷�"+NOR+RED"ͬʱ����$n"NOR+xue_name[random(sizeof(xue_name))],
"parry_msg" :
"$n��ͷ"+NOR+HIW"�׷�"+NOR"��������,�ƿ�֮������һ��"+HIM"��÷����Ū��"+NOR"����$N����ʽһһ��ס��",
"parry_power":		10,
"dodge"  : -20,
"parry" : -10,
"force" : 100,
"skill_name"  : "����¥",
"damage_type" : "����",
]),
([
"action" : 
RED"ֻ���������������������������һ��"+NOR+HIW"������ѩ��"+NOR+RED"��$n�����ˬ��ͻȻ"+NOR+HIW"һ�ư׷�"+NOR+RED"���������ƿմ���$n"NOR+xue_name[random(sizeof(xue_name))],
"parry_power":		10,
"parry_msg" :
"$n˫�ֲ������ң�һ��"+HIY"������������"+NOR"�������䣬һ˿˿�����������ӿ������$N��æ���лط���",
"dodge"  : -20,
"parry" : -10,
"force" : 100,
"skill_name"  : "����ѩ",
"damage_type" : "����",
]),
([
"action" : 
RED"$N���˿��ţ����ٲ�����һ��"+NOR+HIC"������Ȫ��"+NOR+RED"�������������ˣ�����ԡ�$nֻ���������ԣ�������ݣ�������գ�
����"+NOR+HIW"һ���ư׷�"+NOR+RED"����Ȼ����"NOR+xue_name[random(sizeof(xue_name))],
"parry_power":		10,
"parry_msg" :
"$n��Ūһ��"+HIC"����̶ӳ�¡�"+NOR"���촽������������������������Ū��磬�һ�����ӳ�պ죻���������̽��壬���������������$N����������ʽһ�ͣ���"+NOR+HIW"һ���ư׷�"+NOR"һһ���⡣",
"dodge"  : -20,
"parry" : -20,
"force" : 100,
"skill_name"  : "����Ȫ",
"damage_type" : "����",
]),
});
mapping query_action(object me, object weapon)
{
 if(me->query_temp("BAIFA_perform") )
  {
 return action_baifa[random(sizeof(action_baifa))];
        }
 else{  
 return action[random(sizeof(action))];}
}
string query_parry_msg(object weapon)
{
	return action[random(sizeof(action))]["parry_msg"];
}
int practice_skill(object me) {
    object weapon, target;
    if (!objectp(weapon = me->query_temp("weapon")) ||
	(string)(weapon->query("skill_type")) != "sword")
	return notify_fail("�������������û������ô�������鳤������ :)\n");
//	if( (string)me->query_skill_mapped("force")!= "jiuyin-xinjing")
//     return notify_fail("�����鳤�������������˿���ľ����ķ���������\n");
    if ((int)(me->query("kee")) < 50)
	return notify_fail("���Ѿ���ƣ���ߣ�û��������ȥ����\n");
    me->receive_damage("kee", 30);
    message_vision(baifa[random(sizeof(baifa))], me, target);
    return 1;
}
void skill_improved(object me)
{
        if( (int)me->query_skill("chixin-jian", 1)  % 10 == 0 ) {
                tell_object(me,
                        RED "\n��ͻȻ����һ�ɶ���������ͷ��ֻ������ɱ��....\n\n" NOR);
                me->add("bellicosity", 50);
        }
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;
        if(!me->query_temp("BAIFA_perform")) return 0;
        me->add("force", -damage_bonus);
        me->add("sen", -100);
        
}
string perform_action_file(string action)
{
        return CLASS_D("pansi") + "/chixin-jian/" + action;
}
