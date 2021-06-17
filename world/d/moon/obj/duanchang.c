// created 4/5/1997 by snowcat
#include <ansi.h>
#include <dbase.h>

inherit ITEM;

void create()
{
  set_name(HIB "�ϳ���" NOR, ({ "duanchang book"})); 
  set_weight(1000);
  set("long","һ�������ľ��飬�϶�ٰ�����֮����Ϳ��\n");
  set("unit", "��");
  set("no_give",1);
  set("no_get",1);
  setup();
}

init ()
{
  add_action ("do_read", "read");
}

int do_read (string arg)
{
  object me = this_player();
  string *msgs = ({
    "$N��̾����������Ϊ���\n",
    "$N�ھ��˼����������\n",
    "$N������˼����Ĭ������\n",
    "$N�������Ĵ�������ס�������¡�\n",
    "$N����������飬��ɫ�����\n",
    "$NС�ĵط���һҳ���͵͵�̾������\n",
    "$N���Ű����ϵĴʾ��Ա��Գ���ȴ��һ���������ĳ���\n",
  });
  	if(me->query("family/family_name") != "�¹�" )
  	{
                tell_object (me,"�㲻���¹����ӣ��������Ȿ�飡\n");
                return 1;
        }
        if( me->query("betray/count") )
        {
		tell_object (me,"�����Ķ��⣬�������Ȿ�飡\n");
		return 1;
	}
        if( (string)me->query("gender") !="Ů��")
        {
                tell_object (me,"���Ϊ����֮��,����֪��Ů���ҵ���˼����\n");
                return 1;
         }
        if(me->query("jueqing_cant"))
        {
      		tell_object(me,"���������Ե��\n");
      		return 1;
      	}
        if(me->query("jueqing_known"))
        {
      		tell_object (me,"����Ŀھ��㶼�Ѿ�֪���˰���\n");
      		return 1;
      	}
      	if( !me->query("jueqing/chimeng"))
      	{
      		tell_object (me,"����ȥ���ʳ����ɹðɣ�\n");
      		return 1;
      	}
      	//if( !me->query("jueqing/zhinu"))
      	//	return ("����ȥ��֯Ůʦ��ɣ�");
      	if( !me->query("jueqing/baihua"))
      	{
      		tell_object (me,"����ȥ���ʰٻ����Ӱɣ�\n");
      		return 1;
      	}
      	if( !me->query("jueqing/xiwangmu"))
      	{
      		tell_object (me,"����ȥ��������ĸ�ɣ�\n");
      		return 1;
      	}
  if( base_name(environment(me)) != "/d/moon/change_room" || !present("chang e",environment(me)) )
  {
	    tell_object (me,"�ϳ�����û����ڡ���˼�ݡ������϶���ɣ�\n");
	    return 1;
  }
  if( ! arg || arg != "book" )
  {
	    tell_object (me,"���ʲô�أ�\n");
	    return 1;
  }
  if( me->is_busy() )	
  {
	    tell_object (me,"����æ���أ�û�ն��飡\n");
	    return 1;
  }
  	me->set_temp("no_move",1);
 	me->start_busy(2+random(2));
 	me->add_temp("read_num",1);
  	message_vision (msgs[random(sizeof(msgs))],me);
  if( random( me->query_temp("read_num") ) > 10 )
  {
  	me->delete_temp("read_num");
  	me->start_busy(5+random(2));
  	me->delete("jueqing/xiwangmu");
  	me->delete("jueqing/chimeng");
  	me->delete("jueqing/baihua");
  	message_vision ("$N̾������֪��Ϊ�������ξ��飿\n",me);
  	message_vision ("\n$Nϸϸ��ζ���϶�д�µĶϳ�����ֻ�������м�������֣�����һ���������������齫���������У�\n",me);
  	if( random(me->query_kar()+me->query("cps")+me->query("cor")) > ( 25 - random(me->query("leaf") + me->query("lunhui_zhuanshi")) ) )
  		call_out("finish_read",2,me);
  	else
  		call_out("finish_read2",2,me);
  }
  return 1;
}
int finish_read( object me )
{
	me->delete_temp("no_move");
	me->set("jueqing_known",1);
	me->delete("leaf");
	message_vision ("$N��������������������ǧ��ֱ�Ǽ�֮���ϣ���֮���ҡ�\n",me);	
	message_vision ("��Ȼ$N��˼����һ˿������$Nץס��Ե����һ˿���������۽�������ȫ��֮����һ��ն�£�\n",me);	
	message_vision ("$N����˫����ֻ�����пտգ���������ʵ����裬$N��һ�������ϳ�����Ϊ��ǧ��Ƭ��\n",me);	
	message_vision ("�϶���̾һ�����������ʽ$N��ѧ���ˣ����Ժ����������������Ұɣ�\n",me);	
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���϶�(chang e)��" + me->name() + "���¹���ѧ�����ڻ��ͨ������ѧ��"+HIB"[������ʽ]"+HIC"���϶�����̾��һ������\n\n\n"NOR,users());
	message_vision ("�϶��峪������������ƣ�ǧɽĺѩ��ֻӰ��˭ȥ��\n",me);	
	message_vision ("$N���϶�����Խ����ĸ�������������δ������Ҫѯ�ʣ�ȴ���϶��Ѿ��Ը������顣\n",me);	
	message_vision ("$N���Ṫ�����˳�ȥ��\n",me);	
	me->move("/d/moon/huilang");
	destruct(this_object());
}

int finish_read2( object me )
{
	me->delete_temp("no_move");
	me->set("jueqing_cant",1);
	me->delete("leaf");
	message_vision ("$N��������������������ǧ��ֱ�Ǽ�֮���ϣ���֮���ҡ�\n",me);	
	message_vision ("$N������Ҫ��������ͷ����ȴ��Խ��Խ����ú�������Ȼ�ճմ�������Ȼ�����ˣ�\n",me);	
	message_vision ("$N���ߴ���һ����̾����ǰ����һ������������Ѿ���ʧ����Ӱ���٣�\n",me);	
	message_vision ("$N����˫����ֻ�����пտգ��϶���ǰ������������ղŶ��Ķϳ�����\n",me);	
	message_vision ("�϶���̾һ�����������ʽ$N����������Եѧϰ�ˣ�\n",me);	
	message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"���϶�(chang e)��" + me->name() + "�޷����۽�ն����������"+HIB"[������ʽ]"+HIC"��Ե���϶�����̾��һ������\n\n\n"NOR,users());
	message_vision ("�϶��峪������������Ϊ���ֱ����������\n",me);	
	message_vision ("$N���϶�����Խ����ĸ������������ˡ�\n",me);	
	message_vision ("�϶�����һ�ӣ�$N���˼������˳��ˡ���˼�ݡ���\n",me);	
	me->move("/d/moon/huilang");
	destruct(this_object());
}
