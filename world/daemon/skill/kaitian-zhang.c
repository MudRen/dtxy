//�����Ʒ�
//lestat modi for kunlun 2001
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

mapping *action = ({
([      "action" : "$Nһʽ"HIW"�����֮�����ڿա�"NOR"��˫�Ƽ�����һ�ŵ����İ�����������$n��$l",
        "dodge" : -30,
        "parry" : -25,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$N�����罣��һʽ"HIW"������������������"NOR"������$n��$l��ȥ",
        "dodge" : -30,
        "parry" : -25,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ"HIW"��Ǭ�������������"NOR"������΢��������է��է�ϣ��͵ز���$n��$l",
        "dodge" : -30,
        "parry" : -25,
        "force" : 190,
        "damage_type" : "����"
]),
([      "action" : "$N˫����������������һʽ"HIW"�����������Բ�ͬ��"NOR"���ó�������̵����룬������$n��ȥ",
        "dodge" : -30,
        "parry" : -25,
        "force" : 200,
        "damage_type" : "����"
]),
([      "action" : "$N��������һ�ݣ�ʹ��һʽ"HIW"��ɱ����Ǭ����"NOR"��˫�Ʋ�£����ֱ����$n��$l��ȥ",
        "dodge" : -30,
        "parry" : -25,
        "force" : 160,
        "damage_type" : "����"
]),
([      "action" : "$N����һ�䣬ʹһʽ"HIW"��ϸϸ΢΢��������"NOR"��˫�ƴ�����ɲ�ľ������͵ػ���$n��$l",
        "dodge" : -30,
        "parry" : -25,
        "force" : 180,
        "damage_type" : "����"
]),
([      "action" : "$Nʹһʽ"HIW"�����ι���͸��黡�"NOR"���������أ�������ӯ��ͬʱ��$n��$l��ȥ",
        "dodge" : -30,
        "parry" : -25,
        "force" : 220,
        "damage_type" : "����"
]),
([      "action" : "$Nͻ��һ��"HIW"���������ӳ��⡹"NOR"��˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
        "dodge" : -30,
        "parry" : -25,
        "force" : 200,
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ"HIW"�����Ǭ���������"NOR"��˫�������һ����裬�����ѻ���$n��$l��",
        "dodge" : -30,
        "parry" : -25,
        "force" : 210,
        "damage_type" : "����"
]),
([      "action" : "$Nһʽ"HIW"����Ժ�滨����ѩ��"NOR"����������������˫��һ��һ�ͣ����Ƽ򵥣�ȴ��$n�޷�����",
        "dodge" : -30,
        "parry" : -25,
        "force" : 180,
        "damage_type" : "����"
])
});
mapping *action_baigu = ({
([  "action" : HIW"$N����΢�Σ�һ��"+NOR+BLU"�����ƺ�����������"+NOR+HIW"��ʮָ��ꪣ�����$n��"+NOR+xue_name[random(sizeof(xue_name))],
    "force" : 100,
    "dodge" : -10,
    "damage_type" : "����",
    "parry" : -20,
    "skill_name" : "���ƺ���������" ,
]),
([  "action" : HIW"$N������磬ʮָ΢΢������һ��"+NOR+HIR"����������Ц������"+NOR+HIW"ץ��$n��"+NOR+xue_name[random(sizeof(xue_name))],  
    "force" : 150,
    "dodge" : -20,
    "damage_type" : "����",
    "parry" : -20,
    "skill_name" : "��������Ц����" ,
]),
([  "action" : HIW"$N˫�ֺ������֣�һ��"+NOR+CYN"�����ܵǳ�����Ϸ��"+NOR+HIW"�����Ȱ��ץ��$n��"+NOR+xue_name[random(sizeof(xue_name))],  
    "force" : 150,
    "dodge" : -10,
    "damage_type" : "����",
    "parry" : -5,
    "skill_name" : "���ܵǳ�����Ϸ" ,
]),
([  "action" : HIW"$N���ֵ��ػ��������ּ�����һ��"+NOR+HIC"������˭�����˹���"+NOR+HIW"���͵�ץ��$n��"+NOR+xue_name[random(sizeof(xue_name))],
    "force" : 150,
    "dodge" : -10,
    "damage_type" : "����",
    "parry" : -10,
    "skill_name" : "����˭�����˹�" ,
]),
([  "action" : HIW"$Nʹһ��"+NOR+HIB"��һ�����󷽷�����"+NOR+HIW"����������ľ��磬ײ��$n"NOR,
    "force" : 200,
    "dodge" : -10,
    "damage_type" : "����",
    "parry" : -10,
    "skill_name" : "һ�����󷽷���" ,
]),
([  "action" : HIW"$N���ޱ��飬˫�ۺ�����ҵؼ��ӣ�ʹ��"+NOR+HIB"��������ʱ�����ԡ�"+NOR+HIW"��ʮָ    
���������Ѹ���ޱȵ�Ϯ��$nȫ�������Ѩ"NOR,
    "force" : 150,
    "dodge" : -20,
    "damage_type" : "����",
    "parry" : -10,
    "skill_name" : "������ʱ������" ,
]),
([  "action" : CYN"$Nʹ��"+NOR+YEL"�������������뾻��"+NOR+CYN"����Ȼ������ϣ�����$n��ת��Ȧ��$n����  
�����Ҽ䣬$N����Ȼͣ��$n������ֻ���һ����Ȧ���������ֳ����Ȧ��ץ$n��"+NOR+xue_name[random(sizeof(xue_name))],  
    "force" : 150,
    "dodge" : -5,
    "damage_type" : "����",
    "parry" : -10,
    "skill_name" : "�����������뾻" ,
]),
([  "action" : CYN"$NͻȻ˫��ƽ�٣�$nһ�������ڲ²�䣬���$Nವ�һ�½�˫��    
�ջ���ǰ������һ��"+NOR+HIW"��δ��֪����֪�ա�"+NOR+CYN"����ָ�繳��ֱץ��$n��"+NOR+xue_name[random(sizeof(xue_name))],
    "force" : 100,
    "dodge" : -10,
    "damage_type" : "����",
    "parry" : -20,
    "skill_name" : "δ��֪����֪��" ,
]),
});
int valid_enable(string usage) { return usage=="unarmed" ; }

mapping query_action(object me, object weapon)
{
        mapping my;
        my = me->query_entire_dbase();
 if(me->query_temp("BAIGU_perform") )
  {
 return action_baigu[random(sizeof(action_baigu))];
        }
 else{  
 return action[random(sizeof(action))];}
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�����翪���Ʊ�����֡�\n");
        if ((int)me->query_skill("xuanzong-force", 1) < 20)
                return notify_fail("��������ķ���򲻹����޷�ѧ���翪���ơ�\n");
        if ((int)me->query("max_force") < 100)
                return notify_fail("�������̫�����޷������翪���ơ�\n");
        return 1;
}

int practice_skill(object me)
{
        if ((int)me->query("kee") < 30)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("force") < 40)
                return notify_fail("����������������翪���ơ�\n");
        me->receive_damage("kee", 30);
        me->add("force", -10);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2) > victim->query_str()/10) {
                victim->receive_wound("kee", damage_bonus / 4 );
                switch(random(3)) {
                        case 0: return HIB"��������������һ�����죬�����ǹ����������\n"NOR;
                        case 1: return HIB"$N����һ�£�$n��$l������������һ�����죡\n"NOR;
                        case 2: return HIB"ֻ����$n��$l��������һ�� ...\n"NOR;
                }
        }
}
string perform_action_file(string action)
{
        return CLASS_D("kunlun") +"/kaitian-zhang/" + action;
}


