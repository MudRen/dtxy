//Cracked by Roath

// dhxy-evil 2000.7.7
inherit FORCE;
string type() { return "force"; }

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 10)
                return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ����������\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("��������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
        return CLASS_D("shushan") + "/xiantian-force/" + func;
}
