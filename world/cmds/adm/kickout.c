// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// kickout.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
   object link_ob;
   object obj;
   
   if( !arg )
        return notify_fail("��Ҫ��˭�ϳ�ȥ��\n");

   if (arg == "me")  return notify_fail("�������뽵ְ����Һ���suicide -f\n");

   if  (!objectp(obj= find_player(arg)))
     return notify_fail("����Ҳ����ߣ���λ��ǷŹ����ɡ�\n");
  
   if ( obj == me )
     return notify_fail("�������뽵ְ����Һ���suicide -f\n");
   
   link_ob = obj->query_temp("link_ob");
   obj->set("is_banned_char",1);
   obj->save();
   message_vision(HIY"$N���һ���������Ͻ���һ�����罫$n��Ϊ�ҽ���\n"NOR,me,obj);
   log_file("kickout", sprintf("%s(%s) kickout user %s (%s) at (%s)\n",
    me->query("name"),me->query("id"), obj->query("name"),obj->query("id"), ctime(time())));
   seteuid(ROOT_UID);
   destruct(link_ob);
   destruct(obj);
   seteuid(getuid(me));
   return 1;
}

