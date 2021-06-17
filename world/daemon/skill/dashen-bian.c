inherit SKILL;
#include <ansi.h>
mapping *action = ({
        ([      "action":
"$Nʹһ��"+BLINK""+HIW"�������˼��䷲����"NOR+"������$w��Ϊһ���ڹ�����$n��$l",
                "dodge":                -5,
                "parry":                -10,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"ֻ��$N������ת��ʹ��"+BLINK""+HIG"��������ɧ��Ұ�ˡ�"NOR+"��һ������г����������$n��$l",
                "dodge":                -35,
                "parry":                -5,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����������һʽ"+BLINK""+HIC"�������������׾��"NOR+"���������Ӱ, $nֻ���������ڹ�Ϯ������֪���������",
                "dodge":                -10,
                "parry":                -15,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����$w����һɨ��һ��"+BLINK""+HIY"������������������"NOR+"һƬ��Ӱɨ��$n�� $n��ܲ�����������һ�£���ͷһ���̲�ס�³�һ����Ѫ",
                "dodge":                -30,
                "parry":                -5,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����$wһ����ֻ�������Ӱ��������ա�\n��һ��"+BLINK""+HIB"��Ϫδ������Ρ� "NOR+"ֻ����$n�ۻ����ң����ﻹ���м�",
                "dodge":                -20,
                "parry":                -20,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$nֻ������ǰһ����$N����Ȼ������$n�������$wֱָ$n�ĺ��ģ� ����һʽ"+BLINK""+HIR"��μˮ��֪�����롹"NOR+"",  
                "dodge":                -35,
                "parry":                -5,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N�������ܣ�һʽ"+BLINK""+HIG"����ʷ��ƿ���ҵ��"NOR+"���������У� ���ƴ���������$wֱָ$n��������",
                "dodge":                -5,
                "parry":                -10,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����һ����Ц������$wһ��"+BLINK""+HIM"������˰��쳤����"NOR+"����$n���ϣ�$nֻ����ǰһ�ڡ�������˹�ȥ",
                "dodge":                -5,
                "parry":                -10,
                "damage":               50,
                "force":               10,
                "damage_type":  "����"
        ]),
});
int valid_learn(object me)
{
        object ob;
        if( (int)me->query("max_force") < 50 )
                return notify_fail("�������������û�а취������޷���\n");
        if( (string)me->query_skill_mapped("force")!= "xuanzong-force")
                return notify_fail("����޷�������������ķ���������\n");
        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "mace" )
                return notify_fail("���������һ�����Ӳ�������\n");
        return 1;
}
int valid_enable(string usage)
{
        return usage=="mace" || usage=="parry";
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
int practice_skill(object me)
{
        if( (int)me->query("kee") < 30
        ||      (int)me->query("force") < 3 )
                return notify_fail("�����������������û�а취��ϰ����޷���\n");
        me->receive_damage("kee", 30);
        me->add("force", -3);
        write("�㰴����ѧ����һ�����޷���\n");
        return 1;
}
string perform_action_file(string func)
{
return CLASS_D("kunlun") + "/dashen-bian/" + func;
}
