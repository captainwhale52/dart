/*
 * Copyright (c) 2015, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Michael X. Grey <mxgrey@gatech.edu>
 *
 * Georgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#include "dart/dynamics/SimpleFrame.h"
#include "dart/simulation/World.h"
#include "dart/gui/SimWindow.h"

#include "dart/dynamics/BoxShape.h"
#include "dart/dynamics/EllipsoidShape.h"

using namespace dart::dynamics;

int main(int argc, char* argv[])
{
  dart::simulation::World myWorld;

  Eigen::Isometry3d tf1(Eigen::Isometry3d::Identity());
  tf1.translate(Eigen::Vector3d(0.1,-0.1,0));

  Eigen::Isometry3d tf2(Eigen::Isometry3d::Identity());
  tf2.translate(Eigen::Vector3d(0,0.1,0));
  tf2.rotate(Eigen::AngleAxisd(45.0*M_PI/180.0, Eigen::Vector3d(1,0,0)));

  Eigen::Isometry3d tf3(Eigen::Isometry3d::Identity());
  tf3.translate(Eigen::Vector3d(0,0,0.1));
  tf3.rotate(Eigen::AngleAxisd(60*M_PI/180.0, Eigen::Vector3d(0,1,0)));

  SimpleFrame F1(Frame::World(), "F1", tf1);
  F1.addVisualizationShape(new BoxShape(Eigen::Vector3d(0.05, 0.05, 0.02)));
  SimpleFrame F2(&F1, "F2", tf2);
  F2.addVisualizationShape(new BoxShape(Eigen::Vector3d(0.05, 0.05, 0.02)));
  SimpleFrame F3(&F2, "F3", tf3);
  F3.addVisualizationShape(new BoxShape(Eigen::Vector3d(0.05, 0.05, 0.02)));

  // Note: Adding a Frame to the world will also cause all Entities that descend
  // from that Frame to be rendered, but they will not be counted in the list of
  // Entities in myWorld. So F2 and F3 will be rendered by simply adding the F1
  // Frame
  myWorld.addEntity(&F1);

  SimpleFrame A(Frame::World(), "A");
  A.addVisualizationShape(new EllipsoidShape(Eigen::Vector3d(0.02,0.02,0.02)));
  SimpleFrame A1(&A, "A1", F1.getTransform(&A));
  A1.addVisualizationShape(new EllipsoidShape(Eigen::Vector3d(0.01,0.01,0.01)));
  SimpleFrame A2(&A, "A2", F2.getTransform(&A));
  A2.addVisualizationShape(new EllipsoidShape(Eigen::Vector3d(0.01,0.01,0.01)));
  SimpleFrame A3(&A, "A3", F3.getTransform(&A));
  A3.addVisualizationShape(new EllipsoidShape(Eigen::Vector3d(0.01,0.01,0.01)));

  myWorld.addEntity(&A);

  // CAREFUL: For an Entity (or Frame) that gets added to the world to be
  // rendered correctly, it must be a child of the World Frame
  // TODO(MXG): Fix this issue ^

  dart::gui::SimWindow window;
  window.setWorld(&myWorld);

  glutInit(&argc, argv);
  window.initWindow(640, 480, "Simple Frames");
  glutMainLoop();
}
