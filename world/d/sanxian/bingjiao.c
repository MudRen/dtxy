// writted by mind

inherit ROOM;
void create()
{
        set("short", "����");
        set("long", @LONG
��������Ů������һ���޴���ѣ�ԭ������Ϊ�ʼҴ������ʳ��ģ�
������Ȼ�Ѿ��ķϣ���������ı�����Ȼ�ѵ������ģ�����ǽ���Ѿ���
�˺��ı��������������Ŵ��۵Ĺ⣬��ô������ĵط��������Ѿ�͸
����ȥ�������վã��Ѿ����亮�䣬������°��ʱ���������ˡ�
LONG
        );
        set("exits", ([ 
  "out" : "/d/qujing/nuerguo/shanpo",
]));
        set("objects", ([
                
       ]) );
        
        setup();
        
}

void init ()
{
  add_action ("do_around","around");
  add_action("do_study", "xiulian");
}

int do_around ()
{
  object me = this_player ();
  message_vision ("$N��������ţ�������Χ�ĺ�����\n",me);  
  if(!me->query("m_success/���ǵ�"))
  {
    message_vision ("$N���·��ƺ�Ҳ��ʼ�����\n",me);
    call_out("fainting",5,me);  
    return 1;
  }
  if(!me->query_skill("bingpo-hand", 1)){
  message_vision("$Nʹ���ٽ����֣���ͣ������Ϣ������������Ȼ�����һ��ȭ����\n",me);
  me->set_skill("bingpo-hand",1);}
  return 1;
}


void fainting (object me)
{
        message_vision("ͻȻ$N�촽���෢�ϣ���ɫ�԰ף�һ�����ĵ��ڵ��ϡ�����\n", me);
        me->set("m_success/���ǵ�",1);
        me->die();
}

int do_study()
{       
        object me=this_player();
        int sen_cost, kee_cost, force_cost, gain;

        if( me->is_busy() )
                return notify_fail("��æ�ĺܣ����й���������\n");
        if( me->is_fighting() )
                return notify_fail("��ѧ�������������ˣ�\n");
        if( (int)me->query_skill("literate", 1) < 40)
                return notify_fail("���Ļ�̫�ͣ�\n");
        if( (int)me->query_skill("unarmed", 1) < 40)
                return notify_fail("�㻹����ѧ����ȭ�Ź���ɡ�\n");
        if( (int)me->query_skill("bingpo-hand", 1) >= 40)
                return notify_fail("��о������Ѿ����ʺ������ˡ�\n");
        if( (int)me->query("max_force") < 400)
                return notify_fail("��������㣬�����ˡ�\n");

        sen_cost = 45 - (int)me->query_int();
        if( (int)me->query("sen") < sen_cost )
                return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");

        kee_cost = 45 - (int)me->query_con();
        if( (int)me->query("kee") < kee_cost )
                return notify_fail("�����ڻ�������������Ϣ��Ϣ�ˡ�\n");

        force_cost = 20;
        if( (int)me->query("force") < force_cost )
                return notify_fail("���������᲻�����ˣ�����Ϣ��Ϣ�ˡ�\n");

        me->receive_damage("sen", sen_cost);
        me->receive_damage("kee", kee_cost);
        me->add("force", - force_cost);

        gain = (int)me->query("int")/2 + (int)me->query("con")/2 + 1 + random(10);

        me->improve_skill("bingpo-hand", gain);

        write("��ʩչȭ�ţ��߶���Ϣ���ԡ����ǵ����������˽⡣\n");

        tell_room( environment(me), me->name() + "�����飬�ֽŹ�����趯��\n", ({me}));

        return 1;
}
