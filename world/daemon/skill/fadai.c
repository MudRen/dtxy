inherit SKILL;
void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me) 
{
return notify_fail("������ֻ����ʵ����������ᡣ\n");
        return 1;
}

int practice_skill(object me)
{       
return notify_fail("������ֻ����ʵ����������ᡣ\n");
}
