inherit ITEM;

#include <ansi.h>


int do_he(string);

void create() 
  {
   set_name(YEL "������" NOR,({"tang"}));
   set("long","һ�뻨�����̵�"+this_object()->query("name")+"������(he)ζ����\n");
   set_weight(50);
   set("unit","��");
   setup();
  }

void init()
{
  add_action("do_he", "he");
}

int do_he(string arg)
  {
   object me=this_object();
   object who=this_player();
   if( !this_object()->id(arg) ) return notify_fail("�����ɶ��\n");
   message_vision("$N����"+me->query("name")+"��ཹ�ཱུĺ�����ȥ��\n", who);
   if ( me->query("prices")<= 0 )  message_vision("��ʲô��ζҲû��������\n", who);
   else if( who->query("piaoxue/handu") == 1 )
   {
   	message_vision("$N������������ǿ����û�³�����\n", who);
      	who->improve_skill("ningxie-force", me->query("prices"));
      	tell_object(who,"����ת��Ѫ�񹦣�С������ĶԿ��Ŷ�����ҩ����\n");
      	tell_object(who,"�����Ѫ�񹦵��������ˡ�\n");
      	who->set("piaoxue/handu",2);
      	tell_object(who, YEL "��ı�����Ѫ��������"
        	 +chinese_number(me->query("prices"))+"�㣡\n" NOR);
        who->unconcious();
   }
   else if( who->query("piaoxue/handu") == 2 )
   {
   	message_vision("$N������������ǿ����û�³�����\n", who);
      	who->improve_skill("ningxie-force", me->query("prices"));
      	tell_object(who,"����ת��Ѫ�񹦣�С������ĶԿ��Ŷ�����ҩ����\n");
      	tell_object(who,"�����Ѫ�񹦵��������ˡ�\n");
      	tell_object(who, YEL "��ı�����Ѫ��������"
         	+chinese_number(me->query("prices"))+"�㣡\n" NOR);
        who->delete("piaoxue");
        if( random(who->query("int")+who->query("con")) > 20 - random( who->query("lunhui_zhuanshi") ) )
        {
        	who->set("piaoxue_known",1);
        	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����������(dapeng mingwang)��" + who->name() + "�������ˣ�ƾ�����Կ����أ��Ӵ��Ժ��پ��º����ˣ�\n\n\n"NOR,users());
        }
        else
        {
        	who->set("piaoxue_cant",1);
        	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"����������(dapeng mingwang)��" + who->name() + "�������ˣ�ƾ�����Կ����أ���ϧδ�������ȷ������Ҳ�޷�ѧϰ��ѩɽ��������书�ˣ�\n\n\n"NOR,users());
        }
        who->unconcious();
   }
   else if ( (int)who->query_skill("ningxie-force", 1) < 10 
   || (int)who->query_skill("ningxie-force", 1) > 199  )  
     {
      message_vision("$Nֻ�е�һ����ģ�������ת��\n", who);
      who->unconcious();
     }
   else 
     {
      message_vision("$N������������ǿ����û�³�����\n", who);
      who->improve_skill("ningxie-force", me->query("prices"));
      tell_object(who,"��ֻ�е�����������ʮ��С���������Ҵ̣���ʹ����������"
         +"�Ž�������ҩ����ȫ���⡣\n");
      tell_object(who, YEL "��ı�����Ѫ��������"
         +chinese_number(me->query("prices"))+"�㣡\n" NOR);
     } 
   destruct(me);
   return 1;
  }

