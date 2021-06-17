#include <ansi.h>

inherit NPC;

int reset_status();

void init()
{
	::init();
	add_action("do_train", "train");
        
        remove_call_out("check_id");
        call_out("check_id",2);
        
 }

void check_id()
{
        
        object who,*enemy;
        object me = this_object();
        object rider_obj = me->query_temp("rider");
        int i,diff;
        string owner_id = query("owner");
        
// ûѵ
        if(!rider_obj)
        {
           remove_call_out("check_id");
           call_out("check_id",2);
           return ; 
        }
        
        if(!owner_id) 
        {
         	remove_call_out("check_id");
                call_out("check_id",10);
        	return ; 
        	} ;
//�˲���
        who = present(owner_id, environment(me));
        if(!objectp(who)||!living(who))
        {
         	remove_call_out("check_id");
                call_out("check_id",4);
        	return ; 
        	} ;
// û��        
        	
       if(rider_obj->query("name")!=(string)who->query("name"))
       {
       	 	remove_call_out("check_id");
                call_out("check_id",4);
        	return ; 
      	} ;
        
        
        enemy=who->query_enemy();
        if (!enemy||who->is_fighting()==0)
        {
//                  if(me->is_fighting()==1)
//                  me->remove_all_killer();
                  remove_call_out("check_id");
                  call_out("check_id",4);
        	  return ; 
        } ;
               
        
        i=sizeof(enemy);
        while(i--) {
               if( enemy[i] && living(enemy[i]) ) {
       
       diff=50-who->query_kar();
       
       if(random(diff*diff) < 20 ) {
        message_vision(HIW "ͻȻ$N"+HIW"���Ϸų�ҫ�۵ľ�ɫ����,$n�����˾�Ȼ�����Լ�����ս����\n" NOR, me, enemy[i]); 
                   enemy[i]->start_busy(random(5));
               }}
        } 
    	        remove_call_out("check_id");
                call_out("check_id",2);
        	return ; 
   
}

int do_train(string arg)
{
	object me, where;
	me=this_player();
	where=environment(me);
/*
	if( where->query("no_fight") )
		return notify_fail("��ȫ���ڲ���ѵ�ޣ�\n");
*/
	if( !arg )
		return notify_fail("��Ҫѱ��ʲô��\n");
	if( arg != (string)this_object()->query("id") )
		return notify_fail("��Ҫѱ��ʲô��\n");
	if( this_object()->query_temp("rider") )
		return notify_fail("��ƥ�������Ѿ������ˡ�\n");
	if( (string)this_object()->query("owner")==(string)me->query("id") )
		return notify_fail("��ƥ�����Ѿ�������ˡ�\n");
	if( this_object()->is_fighting() )
		return notify_fail("��ƥ�����Ѿ�����Ͼ�ˡ�\n");
	if( !living(this_object()) )
		return notify_fail("����ˣʲô���磿\n");
	if( where->query("no_fight") ) {
		random_move();
		return 1;
	}


	message_vision(HIM"$N����ǰȥ��$nŤ���һ�š�\n"NOR, me, this_object());

       	this_object()->set_temp("owner",me->query("id"));
	reset_status();
	this_object()->kill_ob(me);
	me->fight_ob(this_object());

	return 1;
}

void unconcious()
{
        string owner;
        object owner_ob;
        owner = query_temp("owner");	
	
	if( owner ) {
	
	owner_ob= find_player(owner);
	
	if( objectp(owner_ob = find_player(owner)) ) {
	        if( (object)query_temp("last_damage_from") == owner_ob ) {
			set("owner", owner_ob->query("id"));
			delete_temp("owner");
			reset_status();
			this_object()->remove_all_killer();
			this_object()->set("attitude", "heroism");
			message_vision(HIY"\n$N��ͷ��β����ʾ������\n"NOR, this_object());
			return;
        	}
	}
	}
//	message_vision(HIY"$N run away!\n"NOR, this_object());
	die();
//	::unconcious();
}



int reset_status()
{
	object me=this_object();
	me->set("eff_kee", (int)me->query("max_kee"));
	me->set("kee", (int)me->query("max_kee"));
	me->set("eff_sen", (int)me->query("max_sen"));
	me->set("sen", (int)me->query("max_sen"));

	return 1;
}


