// suicide.c by canoe

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	if( me->is_busy() )
		return notify_fail("����һ��������û��ɡ�\n");

	if( !arg ) {
		write("������Ͷ̥��\n");
		return 1;
	}

	if( arg!="-f" )
		return notify_fail("��ɱ�����֣�����Ҫ��Զ������������Ͷ̥��\n");

	if(wizardp(me))
	    return notify_fail("�벻Ҫ��ɱ����ʦ�ʺţ�лл��\n");

	ob = me->query_temp("link_ob");
   	if( !ob )
   	    return notify_fail("�㲻������;��������,������ɱ��\n");;
        while( ob && ob->is_character() ) ob = ob->query_temp("link_ob");
      if(!me->query_temp("suicide")||time()-(int)me->query_temp("suicide")>30)
        CHANNEL_D->do_channel(this_object(),"rumor",me->name()+"�ƺ���Ӧ���˴������εĶ�����������ùġ�");
	me->set_temp("suicide",time());

        if(ob->query("super_password"))
      {
        write("�����ѡ����Զ��������ɱ��ʽ�������������Ͼ���Զɾ���ˣ������\n"
                "���������ȷ���Ļ����������Ĺ������룺");
        input_to("check_super_password",1,me,1);
        return 1;
      }
      else
      {
      	 write("�����ѡ����Զ��������ɱ��ʽ�������������Ͼ���Զɾ���ˣ������\n"
                "�����������Ϊ��û���趨�������룬�������������ĵ�½���룺");
         input_to("check_password", 1, me, 1);
	return 1;
	}
}

private void check_super_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("super_password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("�����������\n");
		return;
	}

	if (forever) {
		tell_object( me,
			HIR "\n\n�����Ҫ��ɱ�ˣ������ʮ�����ڲ���ڣ�����\n�������ˣ��㻹�кܶ�����û����ɣ�\n\n\n" NOR);
		me->set_temp("suicide_countdown", 30);
		me->start_busy( (: call_other, this_object(), "slow_suicide" :) );
	}
}

private void check_password(string passwd, object me, int forever)
{
	object link_ob;
	string old_pass;

	link_ob = me->query_temp("link_ob");
	old_pass = link_ob->query("password");
	if( crypt(passwd, old_pass)!=old_pass ) {
		write("��½�������\n");
		return;
	}

	if (forever) {
		tell_object( me,
			HIR "\n\n�����Ҫ��ɱ�ˣ������ʮ�����ڲ���ڣ�quit��������������ˡ�\n\n\n" NOR);
		me->set_temp("suicide_countdown", 30);
		me->start_busy( (: call_other, this_object(), "slow_suicide" :) );
	}
}

private int slow_suicide(object me)
{
	object link_ob;
	int stage;
	string myid, couple;

	stage = me->query_temp("suicide_countdown");
	me->add_temp("suicide_countdown", -1);
	if( stage > 1 ) {
		if( stage%5 == 0 )
		  tell_object(me,
			HIR "�㻹�� " + stage + " ���ʱ����Ժ�ڡ�"+
			"(��quit���������)\n" NOR);
		return 1;
	}

	link_ob = me->query_temp("link_ob");
	if( !link_ob ) return 0;

	log_file("static/SUICIDE",
		sprintf("%s(%s) commits a suicide on %s from %s\n", geteuid(me), me->name(), ctime(time()), (string)query_ip_name(me) ) );

	seteuid(getuid());
	me->backup();  //emotion
	rm( link_ob->query_save_file() + __SAVE_EXTENSION__ );
	rm( me->query_save_file() + __SAVE_EXTENSION__ );
	myid=me->query("id");

	// remove player home.
	rm( "/data/playerhomes/h_"+myid+ __SAVE_EXTENSION__ );

	// remove mailbox.
	rm( "/data/mail/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );
         // rm pat
         if(me->query("pet"))
         rm( "/data/pet/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );
	// remove couple's home as well. (the home is registered by the
	// couple.)
	couple=me->query("coupld/id");
	if(couple)
	  rm("/data/mail/"+couple[0..0]+"/"+couple+__SAVE_EXTENSION__);


	write("�ðɣ�������:(\n");
	tell_room(environment(me), me->name() +
		"��ɱ�ˣ��Ժ�����Ҳ������������ˡ�\n", ({me}));
	CHANNEL_D->do_channel(this_object(),"rumor",me->name()+"û�л���ȥ����������������һ����ˡ�");
	destruct(me);
	return 0;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: suicide [-f]

�����Ϊĳ��ԭ���㲻�����, �����ѡ����ɱ.
��ɱ������:

suicide    : ����Ͷ̥
suicide -f : ��Զ�ĳ�ȥ�������, ϵͳ��Ҫ����
             ����������ȷ�����.

������ѡ�� :)

HELP
);
        return 1;
}
