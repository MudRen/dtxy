inherit SKILL;


int valid_enable(string usage) { return usage=="spells"; }

int valid_learn(object me)
{
   if(((int)me->query_skill("buddhism", 1)>1
     || (int)me->query_skill("taiyi",1)>1
     || (int)me->query_skill("dao", 1)>1
     || (int)me->query_skill("seashentong",1)>1
     || (int)me->query_skill("moonshentong", 1)>1
     || (int)me->query_skill("yaofa", 1)>1
     || (int)me->query_skill("gouhunshu", 1)>1
     || (int)me->query_skill("baguazhou", 1)>1
     || (int)me->query_skill("dengxian-dafa", 1)>1
     || (int)me->query_skill("pansi-dafa",1)>1
     || (int)me->query_skill("pingtian-dafa", 1)>1)
     &&(int)me->query_skill("yuxu-spells", 1)>200)
     return notify_fail("�������д������������޷�����ѧϰ�����ɷ���\n");
     
        if( (int)me->query_skill("spells", 1) < 20 )
        return notify_fail("��ķ�����Ϊ����������޷�ѧϰ�����ɷ���\n");
        return 1;
}

string cast_spell_file(string spell)
{
        return CLASS_D("kunlun") + "/yuxu-spells/" + spell;
}

string type() { return "magic"; }

