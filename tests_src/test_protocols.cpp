#include <gtest/gtest.h>

#include "../server_src/protocol_server.h"
#include "../client_src/protocol_client.h"
#include "../common_src/socket.h"
#include "../common_src/liberror.h"
#include "../common_src/action_t.h"

#define PORT_TEST 8081

Socket server ("8081");
Socket client("localhost", "8081");

Socket new_client = server.accept();

ProtocolServer protocol_server(std::move(new_client));
ProtocolClient protocol_client(std::move(client));


TEST(ProtocolTest, ActionSendReceive) {
    action_t action = {10, true, false, true, false, true, false, false, false, true, false,
                         false, true, true, true, false, false};
    protocol_client.send_action(action);
    action_t action_received = protocol_server.receive_action();


    EXPECT_EQ(action.player_id, action_received.player_id);
    EXPECT_EQ(action.left, action_received.left);
    EXPECT_EQ(action.right, action_received.right);
    EXPECT_EQ(action.up, action_received.up);
    EXPECT_EQ(action.down, action_received.down);

    EXPECT_EQ(action.stop_right, action_received.stop_right);
    EXPECT_EQ(action.stop_left, action_received.stop_left);
    EXPECT_EQ(action.jump, action_received.jump);
    EXPECT_EQ(action.stop_jump, action_received.stop_jump);

    EXPECT_EQ(action.press_action_button, action_received.press_action_button);
    EXPECT_EQ(action.unpress_action_button, action_received.unpress_action_button);
    EXPECT_EQ(action.press_pick_up_button, action_received.press_pick_up_button);
    EXPECT_EQ(action.press_throw_button, action_received.press_throw_button);

    EXPECT_EQ(action.press_crouch_button, action_received.press_crouch_button);
    EXPECT_EQ(action.unpress_crouch_button, action_received.unpress_crouch_button);
    EXPECT_EQ(action.press_look_up_button, action_received.press_look_up_button);
    EXPECT_EQ(action.unpress_look_up_button, action_received.unpress_look_up_button);
}  

TEST(ProtocolTest, SendReceiveNumber) {
    int number = 10;
    protocol_client.send_number(number);
    int number_received = protocol_server.receive_number();
    EXPECT_EQ(number, number_received);    
}

TEST(ProtocolTest, SendReceiveSnapshot) {
    sounds_DTO sound = {true, true, true, true, true, true, true, true, true};
    std::vector<duck_DTO> ducks;
    std::vector<bullet_DTO> bullets;
    std::vector<weapon_DTO> weapons;
    std::vector<box_DTO> boxes;
    ducks.resize(10);
    bullets.resize(5);
    weapons.resize(2);
    boxes.resize(1);

    game_snapshot_t snapshot = {10, ducks, 5,  bullets, 
                                2, weapons, 1, boxes, sound};


    protocol_server.sendGameInfo(snapshot);
    uint8_t code = protocol_client.read_number();
    EXPECT_EQ(code, 0x01);
    game_snapshot_t snapshot_received = protocol_client.read_snapshot();

    EXPECT_EQ(snapshot.ducks_len, snapshot_received.ducks_len);
    EXPECT_EQ(snapshot.bullets_len, snapshot_received.bullets_len);
    EXPECT_EQ(snapshot.weapons_len, snapshot_received.weapons_len);
    EXPECT_EQ(snapshot.boxes_len, snapshot_received.boxes_len);

    //sounds
    EXPECT_EQ(snapshot.sounds.death, snapshot_received.sounds.death);
    EXPECT_EQ(snapshot.sounds.shooting_small_weapon, snapshot_received.sounds.shooting_small_weapon);
    EXPECT_EQ(snapshot.sounds.shooting_big_weapon, snapshot_received.sounds.shooting_big_weapon);
    EXPECT_EQ(snapshot.sounds.shooting_laser_weapon, snapshot_received.sounds.shooting_laser_weapon);
    EXPECT_EQ(snapshot.sounds.explotion, snapshot_received.sounds.explotion);
    EXPECT_EQ(snapshot.sounds.duck_sliding, snapshot_received.sounds.duck_sliding);
    EXPECT_EQ(snapshot.sounds.shotgun_recharging, snapshot_received.sounds.shotgun_recharging);
    EXPECT_EQ(snapshot.sounds.sniper_recharging, snapshot_received.sounds.sniper_recharging);
    EXPECT_EQ(snapshot.sounds.duck_struck, snapshot_received.sounds.duck_struck);
}

TEST(ProtocolTest, SendReceiveScore) {
    score_DTO score = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    protocol_server.sendScore(score);

    uint8_t code = protocol_client.read_number();
    EXPECT_EQ(code, 0x02);

    score_DTO score_received = protocol_client.read_score();

    EXPECT_EQ(score.amount_of_ducks, score_received.amount_of_ducks);
    EXPECT_EQ(score.first_place_id, score_received.first_place_id);
    EXPECT_EQ(score.second_place_id, score_received.second_place_id);
    EXPECT_EQ(score.third_place_id, score_received.third_place_id);
    EXPECT_EQ(score.fourth_place_id, score_received.fourth_place_id);

    EXPECT_EQ(score.first_place_score, score_received.first_place_score);
    EXPECT_EQ(score.second_place_score, score_received.second_place_score);
    EXPECT_EQ(score.third_place_score, score_received.third_place_score);
    EXPECT_EQ(score.fourth_place_score, score_received.fourth_place_score);
}

TEST(ProtocolTest, SendReceiveFinalScore) {
    score_DTO score = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    protocol_server.sendFinalScore(score);

    uint8_t code = protocol_client.read_number();
    EXPECT_EQ(code, 0x03);

    score_DTO score_received = protocol_client.read_score();

    EXPECT_EQ(score.amount_of_ducks, score_received.amount_of_ducks);
    EXPECT_EQ(score.first_place_id, score_received.first_place_id);
    EXPECT_EQ(score.second_place_id, score_received.second_place_id);
    EXPECT_EQ(score.third_place_id, score_received.third_place_id);
    EXPECT_EQ(score.fourth_place_id, score_received.fourth_place_id);

    EXPECT_EQ(score.first_place_score, score_received.first_place_score);
    EXPECT_EQ(score.second_place_score, score_received.second_place_score);
    EXPECT_EQ(score.third_place_score, score_received.third_place_score);
    EXPECT_EQ(score.fourth_place_score, score_received.fourth_place_score);
}

TEST(ProtocolTest, SendReceiveMap) {
    std::vector<platform_DTO> platforms;
    std::vector<platform_DTO> spawns_platforms;
    platforms.resize(20);
    spawns_platforms.resize(2);
    
    map_structure_t map = {20, 40, 20, platforms, 2, spawns_platforms};
    protocol_server.sendGameStartInfo(map);

    uint8_t code = protocol_client.read_number();
    EXPECT_EQ(code, 0x00);
    map_structure_t map_received = protocol_client.receive_map();

    EXPECT_EQ(map.width, map_received.width);
    EXPECT_EQ(map.height, map_received.height);
    EXPECT_EQ(map.platforms_len, map_received.platforms_len);
    EXPECT_EQ(map.spawns_platforms_len, map_received.spawns_platforms_len);
}

TEST(ProtocolTest, SendString) {
    std::string message = "Hello World!";
    protocol_client.send_string(message);
    
    int size = protocol_server.receive_number();
    EXPECT_EQ(size, message.size());

    for(int i = 0; i < size; i++) {
        int c = protocol_server.receive_number();
        EXPECT_EQ((char)c, message[i]);
    }
}

TEST(ProtocolTest, SocketIsClosed) {
    protocol_client.shutDown();
    protocol_server.receive_number();
    EXPECT_EQ(protocol_server.socket_closed(), true);
}
