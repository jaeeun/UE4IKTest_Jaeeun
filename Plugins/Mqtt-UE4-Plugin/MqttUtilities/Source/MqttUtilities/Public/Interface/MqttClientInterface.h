// Copyright (c) 2019 Nineva Studios

#pragma once

#include "UObject/Interface.h"

#include "Entities/MqttClientConfig.h"
#include "Entities/MqttConnectionData.h"
#include "Entities/MqttMessage.h"
#include "MqttMessageHandlerInterface.h"

#include "MqttClientInterface.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnConnectDelegate);
DECLARE_DYNAMIC_DELEGATE(FOnDisconnectDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPublishDelegate, int, mid);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnMessageDelegate, FMqttMessage, message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnSubscribeDelegate, int, mid,
                                   const TArray<int> &, qos);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnUnsubscribeDelegate, int, mid);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnMqttErrorDelegate, int, code, FString,
                                   message);

UINTERFACE(BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class MQTTUTILITIES_API UMqttClientInterface : public UInterface {
  GENERATED_BODY()
};

class MQTTUTILITIES_API IMqttClientInterface {
  GENERATED_BODY()

public:
  /**
   * Connect to MQTT broker
   * @param connectionData - structure with data required to connect to MQTT
   * broker (host url, port, client id etc.)
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void Connect(FMqttConnectionData connectionData) = 0;

  /**
   * Disconnect from MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void Disconnect() = 0;

  /**
   * Subscribe to topic
   * @param topic - name of the topic
   * @param qos - level of quality of service
   */
  // UFUNCTION(BlueprintCallable, Category = "MQTT")
  // virtual void Subscribe(FString topic, int qos) = 0;

  /**
   * Subscribe to topic (used in blueprint)
   * @param topic - name of the topic
   * @param qos - level of quality of service
   * @param handler - handler event triigered after client received message from
   * MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void Subscribe(FString topic, int qos,
                         const FOnMessageHandlerDelegate &handler) = 0;

  /**
   * Subscribe to topic (used in cpp)
   * @param topic - name of the topic
   * @param qos - level of quality of service
   * @param handler - handler function triigered after client received message
   * from MQTT broker
   */
  virtual void Subscribe(FString topic, int qos,
                         IMqttMessageHandlerInterface *handler) = 0;

  /**
   * Unsubscribe from topic
   * @param topic - name of the topic
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void Unsubscribe(FString topic) = 0;

  /**
   * Publish message
   * @param message - structure with message data (topic, QoS, payload etc.)
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void Publish(FMqttMessage message) = 0;

  /**
   * Set callback for connection event
   * @param onConnectCallback - callback function callback triigered after
   * client successfully established connection with MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void
  SetOnConnectCallback(const FOnConnectDelegate &onConnectCallback) = 0;

  /**
   * Set callback for disconnection event
   * @param onDisconnectCallback - callback function callback triigered after
   * client was disconnected from MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void SetOnDisconnectCallback(
      const FOnDisconnectDelegate &onDisconnectCallback) = 0;

  /**
   * Set callback for message publishing event
   * @param onPublishCallback - callback function callback triigered after
   * client message was published to MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void
  SetOnPublishCallback(const FOnPublishDelegate &onPublishCallback) = 0;

  /**
   * Set callback for message receiving event
   * @param onMessageCallback - callback function callback triigered after
   * client received message from MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void
  SetOnMessageCallback(const FOnMessageDelegate &onMessageCallback) = 0;

  /**
   * Set callback for subscription event
   * @param onSubscribeCallback - callback function callback triigered after
   * client subscribed to topic exposed by MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void
  SetOnSubscribeCallback(const FOnSubscribeDelegate &onSubscribeCallback) = 0;

  /**
   * Set callback for unsubscription event
   * @param onUnsubscribeCallback - callback function callback triigered after
   * client unsubscribed from topic exposed by MQTT broker
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void SetOnUnsubscribeCallback(
      const FOnUnsubscribeDelegate &onUnsubscribeCallback) = 0;

  /**
   * Set callback for error event
   * @param onErrorCallback - callback function callback triigered after any
   * MQTT-related error occured
   */
  UFUNCTION(BlueprintCallable, Category = "MQTT")
  virtual void
  SetOnErrorCallback(const FOnMqttErrorDelegate &onErrorCallback) = 0;
};
