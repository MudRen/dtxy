// changjian.c ����

#include <weapon.h>
inherit SWORD;
inherit NEWITEM;
int do_install(string);
int do_uninstall(string);

string ori_long="һ�ѹ�ע�������Ľ���ֻ�ǽ�������������
�������ƺ��и�������װ (install) Щ������ȥ��\n";
int is_weapon() {
    return 1;
}


void create()
{
	set_name("��", ({"sword" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",ori_long);
                set("orilong",ori_long);
                set("unit", "��");
		set("value", 500);
		set("material", "steel");
		set("wield_msg", "$N��Цһ�����ӱ����ó���$n��\n");
                set("unwield_msg", "$N�����е�$n������У���Ƕ���һ˿Ц�⡣\n");
		set("anqi/allow", 1);
                set("anqi/max", 100);
                set("anqi/now", 0);
	}
	init_sword(25);
	setup();
}
void init()
{                                             
        add_action("do_install", "install");
        add_action("do_uninstall", "uninstall");
}


int do_install(string arg)
  {
   object me=this_object();
   object who=this_player();
   object aq;
   int remain;

   if( !arg)  return notify_fail("����װʲô��\n");
  if (who->is_busy() || who->query_temp("doing_xiudao") ||        who->query_temp("pending/exercising"))
 	return notify_fail("��������æ���ء�\n");

   aq=present(arg, who);
   if (! present(arg, who)) 
        return notify_fail("������û���ⶫ����\n");
   else if( aq->query("name") == me->query("name") ) return notify_fail("װ�Լ���\n");
   else if (aq->query("name") != "����" && aq->query("name") != "����" && aq->query("name") != "��ȸ��") 
        return notify_fail("������̫���ˣ�װ����ȥ��\n");
   else if (me->query("anqi/now") == me->query("anqi/max"))
        return notify_fail(me->query("name")+"�Ѿ�װ�������ˡ�\n");
   else if (me->query("anqi/now") >0 && 
            me->query("anqi/type") != aq->query("name") )
        return notify_fail(me->query("name")+"����װ��ͬ�İ�����\n");
   else  
     {
     message_vision( "$N��"+me->query("name")+"�Ļ��أ���һ"+aq->query("unit")+aq->query("name")+"װ�˽�ȥ��\n",who);

     if (me->query("anqi/now") ==0) me->set("anqi/type",aq->query("name"));
     if (me->query("anqi/now") + aq->query_amount() > me->query("anqi/max")) 
         {
         remain=me->query("anqi/now") + aq->query_amount() - me->query("anqi/max");
         me->set_item_attr("anqi/now", me->query("anqi/max"), who);
         //me->set("anqi/now",me->query("anqi/max"));
         //me->set("long",me->query("orilong")+"�����Ѿ�װ��" +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n");
         me->set_item_attr("long", me->query("orilong")+"�����Ѿ�װ��" +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n", who);
         aq->set_amount(remain);
         }
     else 
         {
         //me->set("anqi/now",me->query("anqi/now") + aq->query_amount());
         //me->set("long",me->query("orilong")+"�����Ѿ�װ��"
         //  +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n");
         me->set_item_attr("anqi/now", me->query("anqi/now") + aq->query_amount(), who);
         me->set_item_attr("long", me->query("orilong")+"�����Ѿ�װ��" +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n", who);
         destruct(aq);
         }
     return 1;
     }
  }

int do_uninstall(string arg)
  {
   object ob;
   object me=this_object();
   object who=this_player();

  if (who->is_busy() || who->query_temp("doing_xiudao") ||        who->query_temp("pending/exercising"))
      return notify_fail("��������æ���ء�\n");
   if( !this_object()->id(arg) ) return notify_fail("�����ʲô��\n");
   else if (me->query("anqi/now") ==0) return notify_fail(me->query("name")+"����ʲôҲû�С�\n");
   else 
     {
      if (me->query("anqi/type") =="����") ob=new("/d/obj/weapon/throwing/yinzhen");
//      else if (me->query("anqi/type") =="��ȸ��") ob=new("/d/obj/weapon/throwing/kongqueling");
      else ob=new("/d/obj/weapon/throwing/kongqueling");
      ob->set_amount(me->query("anqi/now"));
      ob->move(who);
      //me->set("long",ori_long);
      //me->set("anqi/now", 0);
      me->set_item_attr("anqi/now", 0, who);
      me->set_item_attr("long", ori_long, who);
      message_vision("$N��"+me->query("name")+"������һ"+ob->query("unit")+ob->query("name")+"��\n", who);
//      who->start_busy(3);
      return 1;               
     }
  }