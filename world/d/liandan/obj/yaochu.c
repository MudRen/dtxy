//���ָ������йصĶ���,busyԽ��,bugԽ��

#include <ansi.h>
inherit ITEM;

void init()
{
	add_action("do_wayao", "dig");
	//add_action("do_wayao", "wa");
}

void create()
{
	set_name("ҩ��", ({"yao chu", "chu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_drop","��Ҫ�Ҷ����ⶫ�����˻�ʹ��,û����,�ҵ������ݲ�Ҳ���ã�\n");
		set("no_put",1);
		set("long", "����һ�Ѻ��ص�ҩ�����������������ҩ��dig yao����\n");
		set("value", 5000);
	}
	setup();
}

int do_wayao(string arg)
{       object ob;
        object me=this_player();
        if (me->is_busy()||me->query_temp("pending/exercising")) return notify_fail("��������æ���ء�\n");
        if (!arg||arg!="yao") return notify_fail("��Ҫ��ʲô�أ���\n");
        if (me->is_fighting())	return notify_fail("ս���л����ʲô������������\n");
        if (me->query("combat_exp") < 300000) return notify_fail("����书��Ϊ�����㹻�������ҩ��.\n");
        if ((me->query("sen") < 200)) return notify_fail("��ľ������ܼ��У�����Ҳ�ǰ��ڣ�\n");
        if (me->query("kee") < 400 ) return notify_fail("��̫���ˣ���ô���ò������ҩ����\n");
        if (present("baicao xian", environment(me))) return notify_fail("���˼���͵ҩ,���ðɣ�\n");
        if (present("zhengui yaocai", environment(this_object()))||present("putong yaocai",environment(this_object()))) return notify_fail("��֪��,���Ѿ��ڵ�ҩ�ˣ�\n");
        if(environment(this_object()) != me)  return notify_fail("�����ڿ������ڰɣ�\n");
        if (environment(me)->query_temp("wayao1"))
        {
        me->start_busy(random(3)+1);
        message_vision("$N�Ӷ�ҩ�������ꡢ���ꡱ���ڵ�����������,�ƺ�����ʲô������\n",me);
        me->add("kee",-100);
        me->add("sen",-50);
            if(random(7)<3)
      {
        message_vision(HIY"����һ���Ϻ�:�η�����,������ũҩ����Ұ?�ٲ��ɼ������Ƹ���$N��ǰ��\n"NOR,me);
        ob=new(__DIR__"baicaoxian1.c");
        ob->copyskill(ob,me);
        ob->move(environment(me));
        ob->set_leader(me);
        ob->kill_ob(me);
        me->start_busy(1);
      }
      else
      if (random(5)<2||!me->query_temp("killed_zi"))
      {
          message_vision(CYN"һ���ھ���ͨҩ�ľ�����˿����,�����ڰ� :) \n"NOR,me);
      }
      else
      {
        message_vision(YEL"$N���˰��죬���ڰ��ǿ�ҩ��С������ؾ��˳�����\n"NOR,me);
        message_vision(YEL"ҩ�ݵ����ڵ��ˣ���ϧҩ��ȴ��С�����ˡ�\n"NOR,me);
        new(__DIR__"putongyaocai")->move(me);
        me->delete_temp("killed_zi");
        environment(me)->add_temp("wayao1",-1);
        destruct(this_object());
        me->start_busy(1);
      }
      return 1;
   }
      else
   	if (environment(me)->query_temp("wayao2"))
        {
        me->start_busy(1+random(4));
        message_vision(CYN"$N�Ӷ�ҩ����ʼ�ڵ�������������\n"NOR,me);
        me->add("kee",-150);
        me->add("sen",-70);
             if(random(7)<4)
      {
        tell_room(environment(me),HIY"����һ���Ϻ�:�η�����,������ũҩ����Ұ?�ٲ��ɼ������Ƹ���.\n"NOR );
        ob=new(__DIR__"baicaoxian2.c");
        ob->copyskill(ob,me);
        ob->move(environment(me));
        ob->set_leader(me);
        ob->kill_ob(me);
        me->start_busy(1);
      }
      else
      if (random(5)<2||!me->query_temp("killed_zi"))
      {
          message_vision(CYN"һ���ھ����ҩ�ľ�����˿����,�����ڰ� :) \n"NOR,me);
      }
      else
      {
        message_vision(YEL"$N���˰��죬���ڰ��ǿ�ҩ��С������ؾ��˳�����\n"NOR,me);
        message_vision(YEL"ҩ�ݵ����ڵ��ˣ���ϧҩ��ȴ��С�����ˡ�\n"NOR,me);
        new(__DIR__"zhenguiyaocai")->move(me);
        me->delete_temp("killed_zi");
        environment(me)->add_temp("wayao2",-1);
        destruct(this_object());
        me->start_busy(1);
      }
       	return 1;
    }
      return notify_fail("����ʲô��û��,ԭ�����㿴�����ۡ�\n");
}
