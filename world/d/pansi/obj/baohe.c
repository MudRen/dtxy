#include <ansi.h>
#include <dbase.h>
#include <armor.h>

//inherit F_AUTOLOAD;  
inherit ITEM;
inherit F_UNIQUE;
object focusobj;

void create()

{
     set_name(CYN"�¹ⱦ��"NOR, ({ "yueguang baohe","he","baohe" }) );
     set_weight(100);
     set("long","��������μǴ�˵�������ʥ����ϼ���Ӱ����֤���ľ�˵��˲���ƶ�(move)�����á�\n");
     set("value", 0);
     set("material", "steel");
     set("no_drop", "��ô�ѵõ����ƻ������Űɡ�\n");
     set("unit", "��");
}


void init()
{
if (this_player() -> query("family/family_name") != "��˿��" ) {
remove_call_out("free_jingu");
call_out("free_jingu", 10, this_object(), this_player()); 
}
   add_action("do_move", "move");
   add_action("do_mark", "mark");
::init();
}


int do_move()
{
    object me=this_player(); 

  if(me->is_fighting())
     return notify_fail("������㻹����ֻ���п�ȥ�¹ⱦ���أ�\n");
 if(me->is_busy())
     return notify_fail("����æ����......\n");
  if(me->query("baohe")>20)
        {
      me->set("baohe",0);
        tell_object(me,HIY"���Ҫ�����ͻȻ�������е��¹ⱦ���������ڻ���ֻ��������
��������Ϊһ�������ʧ�ڿ����С�\n"NOR);   
        destruct(this_object());
        return 1;
       }


  if( !query("mark_place") ) return notify_fail("���� mark ��Ŀ�ĵ����ϼǺš�\n");

 tell_room(environment(me),HIY+me->query("name")+"�Ѵӻ����ó��¹ⱦ�з��ڵ���,������:\n"HIR"
    ������������,����������~~~~��\n"HIY
      
                        "һʱ��ɳ����..... "
                        "�����ſ���ʱ,"+me->query("name")+"����Ӱ�Ѿ���ʧ�������ɳ֮��.\n\n"NOR,me);
 
       tell_object(me,HIY"��˫��΢�գ�����������������䣺"
                        "������������Ǭ���󷨣��ߣ���\n"
                        "�����Ӱ�Ѿ���ʧ�������ɳ֮��.\n"NOR);
tell_room(environment(me),HIG"��������˵ľ��������ۡ�������������������������\n"NOR,me);

        me->move(query("mark_place"));
                message_vision(HIY"$N����ӰͻȻ������һ����֮�С�\n"NOR, me);
             me->add("baohe",1);

       return 1;
}


int do_mark()
{
    object me=this_player(); 

  if(me->is_fighting())
     return notify_fail("������㻹����ֻ���п�ȥ�ñ����أ�\n");
if (this_player() -> query("family/family_name") != "��˿��" ) {
tell_object(me, HIR"��·���������˵���������ˣ���֮���á�\n"
+ "����һ�����죬�¹ⱦ�����ڿն�ȥ��������һ˿�ۼ���\n\n"NOR);
destruct(this_object());
return 1;
}

  if(me->query("baohe")>20)
         {
      me->set("baohe",0);
        tell_object(me,HIY"���Ҫ�����ͻȻ�������е��¹ⱦ���������ڻ���ֻ��������
��������Ϊһ�������ʧ�ڿ����С�\n"NOR);   
        destruct(this_object());
        return 1;
       }

  set("mark_place",base_name(environment(me)));

  tell_room(environment(me),HIY+me->query("name")+"���������¹ⱦ�У������������˼������\n"NOR,me);
 
  tell_object(me,"����������¹ⱦ�У������������˼������\n"
            +HIY"ͻȻ�ӱ��������һ������ֱ����������\n"NOR);
       return 1;
}

//int query_autoload() { return 1; }

void free_jingu(object ob, object who)
{
        if(!who || !ob) return;
        if (who -> query("family/family_name") != "��˿��" ) {
             tell_object(who, HIR"��·���������˵���������ˣ���֮���á�\n"
       + "����һ�����죬�¹ⱦ�����ڿն�ȥ��������һ˿�ۼ���\n\n"NOR);
        destruct(ob);
   }
  else { 
           call_out("free_jingu", 10, ob, who);
  }
    return;
}
