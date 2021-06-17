// chunqiu, level 61-100

inherit ITEM;
void init();

void create()
{
  set_name("�����", ({"chunqiu", "book","shu"}));
  set_weight(1000);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "һ�������ɫ��С���ӣ������ţ�����ս����������ԣ�������ת��\n");
    set("material", "cloth");
    set("value", 125);
  }
}

void init()
{
  if (!wizardp(this_player())) {
    set("no_drop",1);
    set("no_sell",1);
    set("no_give",1);
  }
  add_action("do_read", "read");
//  call_out ("destroy_book", 10800);
}

int do_read(string arg)
{
  object me=this_player(),book=this_object();
  int sen_cost, gain,forcelev,exp;

  if( !book->id(arg) ) return notify_fail("��Ҫ��ʲô��\n");
  if( environment(book)!=me ) return notify_fail("��Ҫ����������\n");
  if(me->is_busy()) return notify_fail("������æ���أ����ǵȾ��������ٶ���ɣ�\n");
  if(me->is_fighting()) return notify_fail("����ĥǹ������������\n");
  if( (int)me->query_skill("literate",1)<60 )
    return notify_fail("����������ϸ���˰��죬����ôҲ��������\n");
  if( (int)me->query_skill("literate",1)>100 )
    return notify_fail("�����ⷽ���Ѿ��������裬�Ȿ�鲻�����㳤�����١�\n");
  sen_cost=10+(40-(int)me->query_int())+(35-(int)me->query_kar());
if ( sen_cost < 10 ) sen_cost = 10 ;
  if( (int)me->query("sen")<sen_cost )
    return notify_fail("������ͷ�����ͣ�����Ϣ��Ϣ�ˡ�\n");	
	me->receive_damage("sen", sen_cost);
  
  gain = (int)me->query_skill("literate", 1)/5;
  gain -= random((int)me->query_int());
  gain += random(me->query_kar());
  if (gain <= 0) gain = 1;
  me->improve_skill("literate", gain);

  message_vision("$N��ר�ĵ��ж�"+book->query("name")+"��\n", me);
  tell_object(me, "���ж��йض���ʶ�ֵļ��ɣ��ƺ��е��ĵá�\n");

  return 1;
}

void destroy_book()
{
	message_vision("һ��紵����" + (string)this_object()->query("name") + "ƬƬ���䣬����ȥ�ˡ�\n", environment(this_object()));
	destruct(this_object());
}
