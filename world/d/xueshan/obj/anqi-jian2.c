// sgzl

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

int do_install(string);
int do_uninstall(string);

string ori_long="һ��������彣���������ƺ���Щ������װ(install)Щ������ȥ��\n";


void create()
{
        set_name("�����", ({"fenghuang qin", "qin","sword"}));
        set_weight(14000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "һ����ɫ���ɵĹ��٣�������ֻ����ķ�ˣ�����ȥ��˵Ҳ���ϰ���ı����ˡ�\n");
                set("orilong","һ����ɫ���ɵĹ��٣�������ֻ����ķ�ˣ�����ȥ��˵Ҳ���ϰ���ı����ˡ�\n");
                set("unit", "��");
                set("value", 3000);
                set("material", "steel");
                set("wield_msg", "$N�ӱ���ժ��һ��$n���������С�\n");
                set("unwield_msg", "$N�������е�$n��С������ı��ر���\n");;

                set("anqi/allow", 1);
                set("anqi/max", 100);
                set("anqi/now", 0);
        }
        init_sword(60);
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

   if(who->is_busy()) return notify_fail("����æ���ء�\n");
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
     who->start_busy(3);
     if (me->query("anqi/now") ==0) me->set("anqi/type",aq->query("name"));
     if (me->query("anqi/now") + aq->query_amount() > me->query("anqi/max")) 
         {
         remain=me->query("anqi/now") + aq->query_amount() - me->query("anqi/max");
         me->set("anqi/now",me->query("anqi/max"));
         me->set("long",me->query("orilong")+"�����Ѿ�װ��" +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n");
         aq->set_amount(remain);
         }
     else 
         {
         me->set("anqi/now",me->query("anqi/now") + aq->query_amount());
         me->set("long",me->query("orilong")+"�����Ѿ�װ��"
           +chinese_number(me->query("anqi/now"))+aq->query("base_unit")+aq->query("name")+"��������uninstall��\n");
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

   if(who->is_busy()) return notify_fail("����æ���ء�\n");
   if( !this_object()->id(arg) ) return notify_fail("�����ʲô��\n");
   else if (me->query("anqi/now") ==0) return notify_fail(me->query("name")+"����ʲôҲû�С�\n");
   else 
     {
      if (me->query("anqi/type") =="����") ob=new("/d/obj/weapon/throwing/yinzhen");
//      else if (me->query("anqi/type") =="��ȸ��") ob=new("/d/obj/weapon/throwing/kongqueling");
      else ob=new("/d/obj/weapon/throwing/kongqueling");
      ob->set_amount(me->query("anqi/now"));
      ob->move(who);
      me->set("long",ori_long);
      me->set("anqi/now", 0);
      message_vision("$N��"+me->query("name")+"������һ"+ob->query("unit")+ob->query("name")+"��\n", who);
      who->start_busy(3);
      return 1;               
     }
  }




