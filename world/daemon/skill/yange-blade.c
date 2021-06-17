// spring-blade.c

/*
��赶��    dodge  -10    parry  0    damage  20
��赶�����Ʊ��ţ�Ϊ��������֮ʿ��ϲ���˵���������
���ˣ������ں��ܷ�ɱ��ɱ�����֡�
*/

inherit SKILL;

mapping *action = ({
        ([      "action":
"$Nһ�С�ɽ��������������$w����һ�ɿ�磬����$n��$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����$wһ�Σ�������������$n��$l��һ�С��³����ա�ʹ��ǡ���ô�",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N�����㱣�����$wƮҡ������һ�С���Į���бб�Ŀ���$n��$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N����ִ��$w�����ַ��ŵ��������Ƴ���һ�С�������ɽ��ɨ��$n��$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                0,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N��Цһ����һ�С��߷�Ʈҡ��������$w����˿˿����������ϻ���$n��$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                10,
                "damage_type":  "����"
        ]),
        ([      "action":
"$N���һ����ʹ��һ�С������ã����˫�ֽ���$w
���ű��˵�ɱ��������$n��$l",
                "damage":               20,
                "dodge":                -10,
                "parry":                -10,
                "damage_type":  "����"
        ]),
});

        
mapping *action1 = ({        
([      "action":
"$N����Ծ��ֱ�����죬����$wȫ������һ�С���ɽ�续�������϶��¹���$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),
([      "action":
"$N����ᵯ����$w��ʹһ�С�СԷݺ��Ъ����ֱ��$n��$l",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),
([      "action":
"$Nʹ�������ŵ���ࡹ������$w�������ƣ�Ʈ����������$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),
([      "action":
  "$N�����һʹ��������������������������$w��Х��������$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),
([      "action":        
"$N�����ڶ���ʹһ�С��ۿ�����ȥ��������$w����ˮ��Ϯ��$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),   
([      "action":              
"$N��Хһ����ʹһ�С��������ڡ�������$wȦת��Х����ǿ������Х����Ȼһ�壬����$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),     
([      "action":              
"$N����$w������ǧ�����ʹ��������������������$n",
                "damage":               50,
                "dodge":                -50,
                "parry":                -100,
                "damage_type":  "����"
        ]),              
});

int valid_learn(object me)
{
        object ob;

        if( (int)me->query("max_force") < 80 )
                return
notify_fail("�������������û�а취ѧ��赶����\n");

        if( !(ob = me->query_temp("weapon"))
        ||      (string)ob->query("skill_type") != "blade" )
                return
notify_fail("���������һ�ѵ�����ѧ��赶����\n");

        return 1;
}

int valid_enable(string usage)
{
        return (usage=="blade") || (usage=="parry");
}

mapping query_action(object me, object weapon)
{
        if( me->query_temp("dmyg") )
        	return action1[random(sizeof(action1))];
        else
        	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon = me->query_temp("weapon"))
        ||      (string)weapon->query("skill_type") != "blade" )
                return notify_fail("���������һ�ѵ���������������\n");

        if( (int)me->query("kee") < 40 )
                return
notify_fail("����������������ŵ�������������Ϣ��Ϣ�ɡ�\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
        return 1;
}
string perform_action_file(string func)
{
	return __DIR__"yange-blade/" + func;
}

