#ifndef H_MOTION_CALLBACKS
#define H_MOTION_CALLBACKS

#include <osg/Node>
#include <osg/PositionAttitudeTransform>

// Callback class for the spinning motion of the frisbee
class TurnCallback : public osg::NodeCallback {
	public:
		TurnCallback() : rotation(0) {}
		float dr;

		virtual void operator() (osg::Node* n, osg::NodeVisitor* nv) {
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(n);
			// update the angle of rotation a little bit
			rotation += dr;
			pat->setAttitude( osg::Quat(rotation, osg::Vec3(0, 0, 1) ) );
			traverse(n, nv);
		}
		
		void set_delta_rotation(double theta) {
			dr = theta;
		}

	private:
		double rotation;
};

// Callback class for the turning motion of the bike
class SpinCallback : public osg::NodeCallback {
	public:
		SpinCallback() : rotation(0) {}
		float dr;

		virtual void operator() (osg::Node* n, osg::NodeVisitor* nv) {
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(n);
			// update the angle of rotation a little bit
			rotation -=  dr;
			pat->setAttitude( osg::Quat(rotation, osg::Vec3(1, 0, 0) ) );
			traverse(n, nv);
		}

		void spin(float direction) {
			dr = 0.01 * direction;
		}

	private:
		double rotation;
};

// TODO: Finish callback for tilt, or turn x and turn y
// Callback class for the tilting motion of an object
class TiltCallback : public osg::NodeCallback {
	public:
		TiltCallback() : normal(0.0, 0.0) {}

		virtual void operator() (osg::Node* n, osg::NodeVisitor* nv) {
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(n);
			// update the angle of rotation a little bit
			normal.x() += dx;
			normal.y() += dy;
			pat->setAttitude( osg::Quat(dx, osg::Vec3(normal.y(), normal.x(), 0) ) ); // TODO: Wat?
			traverse(n, nv);
		}

		void tilt(int x, int y) {
			if(normal.x() > -0.5 && normal.x() < 0.5)
				dx += 0.01 * x;
			if(normal.y() > -0.1 && normal.y() < 0.1)
				dy += 0.01 * y;
		}

		void reset_tilt() {
			if(normal.x() > 0)
				dx -= 0.01;
			else
				dx += 0.01;
			if(normal.y() > 0)
				dy -= 0.01;
			else
				dy += 0.01;
		}

	private:
		double dx;
		double dy;
		osg::Vec2d normal;
};

// Callback class for the frisbee flyign through the air
class MoveCallback : public osg::NodeCallback {
	public:
		//MoveCallback() : position(0), up(true) {}
		MoveCallback() : xincr(0), yincr(0) {}

		virtual void operator() (osg::Node* n, osg::NodeVisitor* nv) {
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(n);

			osg::Vec3d newPos(pat->getPosition());
			newPos.x() += xincr;
			newPos.y() += yincr;
			pat->setPosition(newPos);
			traverse(n, nv);
		}

		void setXIncr(double dx) { xincr = dx; }
		void setYIncr(double dy) { yincr = dy; }

	private:
		double xincr, yincr;
};

// Callback class for the frisbee flyign through the air
class BounceCallback : public osg::NodeCallback {
	public:
		BounceCallback() : maxChange(0.1), posChange(0), up(true) {}

		virtual void operator() (osg::Node* n, osg::NodeVisitor* nv) {
			osg::PositionAttitudeTransform* pat = dynamic_cast<osg::PositionAttitudeTransform*>(n);

			osg::Vec3d newPos(pat->getPosition());

			if (posChange < -maxChange) up = true;
			else if (posChange > maxChange) up = false;
			if (up)
				posChange += 0.001;
			else
				posChange -= 0.001;

			newPos.x() += posChange;
			pat->setPosition(newPos);
			traverse(n, nv);
		}

	private:
		double maxChange, posChange;
		bool up;
};

#endif //H_MOTION_CALLBACKS

