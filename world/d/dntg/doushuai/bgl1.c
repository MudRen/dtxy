//created by vikee
//2000.10

#include <ansi.h>
inherit ROOM;

void ready_tongming(object ob);

void create()
{
   set("short", "����¯��Ǭ��");
   set("long",@LONG

�����¯���Ĵ���������֮���������У�ֻ�е����������ѵ���

LONG
        );
 
   set("exits", ([
        "east" : __DIR__"bgl2",
        "north" : __DIR__"bgl4",
                "west": __DIR__"bgl6",
                "south": __DIR__"bgl8",
   ]));
   set("valid_startroom", 1);
   set("objects",([
      "/d/dntg/sky/npc/huobing" : 1,      
   ]));
   setup();
}

void init()
{
   object me = this_player();

   if(!me->query("huoyan/time")) return;
   if(me->query_temp("huoyan/calling")) return;
   me->set_temp("huoyan/calling",1);
   call_out("do_check",20,me,this_object());
}

void do_check(object ob, object env)
{
   object guai,me = ob;

   string *msg = ({
      HIY"�ıھ���һ�Ż��棬�յ��㽹ͷ�ö\n"NOR,     
   });
   string *huo = ({
      "/d/dntg/sky/npc/huolong.c",
      "/d/dntg/sky/npc/huoma.c",
      "/d/dntg/sky/npc/huoya.c",
      "/d/dntg/sky/npc/huoshu.c",
   });

   remove_call_out("do_check");
   
   if(!userp(ob)) return;
   tell_object(ob,msg[random(sizeof(msg))]);
   
   if(env != environment(ob) && !ob->is_fighting()
      && living(ob) && random(2) ){
      guai= new(huo[random(sizeof(huo))]);
      guai->move(environment(ob));
          message_vision("ֻ��������������е�����һչ����ʱ�ı����ܴ�����������\n");
      message_vision("�����һ���ͻȻ�ܳ�һֻ$N��\n",guai);
   }
   
   if((int)me->query("huoyan/time") > 20) me->add("huoyan/time",-20);
   else {
      me->set("huoyan/bgl","done");
      me->set("startroom","/d/city/kezhan");
      me->save();
      tell_room(environment(ob),"¯���Ͼ�˵��������ʮ�����ѹ���������Ҳ���ѱ����ɻҽ���\n");
      tell_room(environment(ob),"�Ͼ��߽�һ����ͯ������¯��\n");
      message_vision("¯�Ŵ��ˣ�$N���ġ������˳�ȥ��\n",ob);
      ob->move("/d/dntg/sky/tongmingdian");
      tell_room(environment(ob),"���춡̧��һ������¯����������һ��������ĳ�һ��������\n",ob);
      ready_tongming(ob);
      return;
   }
   me->add("kee",-100);
   call_out("do_check",20,ob,environment(ob));
}

void ready_tongming(object ob)
{
   object guan,*list,laojun;
   int i,n;
   int ysn = 0, lgn = 0;  
   mixed env = find_object("/d/dntg/sky/tongmingdian");

   if(!env) env = "/d/dntg/sky/tongmingdian.c";
   laojun = new(__DIR__"npc/tslj");    
   laojun->command_function("chat ���²��ã�"+ob->name()+"�Ӱ���¯���ӳ����ˣ�\n");
   message_vision(""HIR"$Nŭ����ײ��һ���߷��Ͼ�¯���Ϻ�һ��������ɱ����ͥ�������ǻ���ı�����"NOR"\n",ob);
   destruct(laojun);
   list = all_inventory(env);
   i = sizeof(env);
   while(i--){
      if(list[i]->query("id")=="ling guan" && !userp(list[i])) lgn +=1;
   }
   if( !guan = present("yousheng zhenjun",env)){
      guan = new("/d/dntg/sky/npc/yszj.c");
      guan->move(env);
   }
   guan->command_function("chat "+ob->name()+"���"+RANK_D->query_rude(ob)+"��ͨ�����ˣ�\n");
   message_vision("$N����һ�У�����������٣���$nΧ���м䣡\n",guan,ob);
   if(ysn != 4)
      for(n==0;n< 4-lgn;n++){
         guan = new("/d/dntg/sky/npc/lingguan");
         guan->move(env);
      }
   return;
}



