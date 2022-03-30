// Copyright (c) 2019 Nineva Studios

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"

#include "Entities/MqttMessage.h"
#include "MqttTask.h"

#include <queue>
#include <string>

class UMqttClient;

typedef void (IMqttMessageHandlerInterface::*MessageHandlerFunc)(FMqttMessage);

class FMqttRunnable : public FRunnable {
 public:
  FMqttRunnable(UMqttClient *mqttClient);
  virtual ~FMqttRunnable();

  bool Init() override;
  uint32 Run() override;
  void Stop() override;

  void PushTask(FMqttTaskPtr task);

  void StopRunning();

  bool IsAlive() const;

 private:
  bool bKeepRunning;

  std::queue<FMqttTaskPtr> *TaskQueue;

  FCriticalSection *TaskQueueLock;

  UMqttClient *client;

  TMap<FString, IMqttMessageHandlerInterface *> m_MsgFuncHandler;
  TMap<FString, FOnMessageHandlerDelegate> m_MsgEventHandler;

 public:
  std::string Host;
  std::string ClientId;
  std::string Username;
  std::string Password;

  int32 Port;
  int32 Timeout;

  void OnConnect();
  void OnDisconnect();
  void OnPublished(int mid);
  void OnMessage(FMqttMessage message);
  void OnSubscribe(int mid, const TArray<int> qos);
  void OnUnsubscribe(int mid);
  void OnError(int errCode, FString message);
};